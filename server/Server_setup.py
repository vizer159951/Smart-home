import http.server
import socketserver
import os
import vlc
import base64
from mistralai import Mistral
from time import sleep
import telebot
import threading
from datetime import datetime
import json

api_key = "GoZj1YDIYvMBijJqFKKdPAEayjKaRvj5"
model = "pixtral-12b-2409"

API_TOKEN = '7838685924:AAHAZEa7ovQ1zGwT3KjJIe5UF9a-oa0LAGE'
user_id = "1980347850"
offset_messages = None
lastDetection = None
bot = telebot.TeleBot(API_TOKEN)

streaming_video = False
player = None

thread_lock = threading.Lock()

port = 9000



### БОТ
##########################################################
@bot.message_handler(commands=['start'])
def start_message(message):
    markup = telebot.types.ReplyKeyboardMarkup(resize_keyboard=True)
    markup.add(telebot.types.KeyboardButton("Запросить кадр"))
    markup.add(telebot.types.KeyboardButton("Удалить параметр"))
    bot.send_message(message.from_user.id, text = "Итерфейс обновлен", reply_markup = markup)
@bot.message_handler(content_types=['text'])
def readText(message):
    global user_id, bot
    if message.text == "Запросить кадр":
        with open("video_stream.jpg", 'rb') as file:
            current_time = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
            image = file.read()
            bot.send_photo(user_id, image, caption = current_time)
def run_telebot():
    global bot
    print_with_lock("Запуск бота")
    bot.infinity_polling()
def send_detection(image, text):
    global user_id, bot
    bot.send_photo(user_id, image, caption=text)




### СЕРВЕР
##########################################################
def delete_all_data(self):
    with open("images_config.json", 'w', encoding='utf-8') as file:
                json.dump([], file, ensure_ascii=False, indent=4)
    folder = "images"
    for filename in os.listdir(folder):
        path = os.path.join(folder, filename)
        os.unlink(path)
    self.send_response(200)
    self.end_headers()
    print_with_lock('Все детекции удалены!')
def save_parametres(self):
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length)
            data = json.loads(post_data.decode('utf-8'))
            with open("parametres.json", 'w', encoding='utf-8') as file:
                json.dump(data, file, ensure_ascii=False, indent=4)
            self.send_response(200)
            self.end_headers()
            print_with_lock("Параметры были приняты и сохранены")
class Handler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        path = self.path[1:]
        if self.path == "/":
            self.send_response(200)
            self.send_header("Content-type", 'text/html; charset=utf-8')
            self.end_headers()
            with open('Html.html', encoding='utf-8') as file:
                data = file.read()
                self.wfile.write(bytes(data, "utf-8"))
        elif self.path.startswith('/images/'):
            self.send_response(200)
            self.send_header('Content-Type', 'image/jpeg')
            self.end_headers()
            with open(path, 'rb') as file:
                data = file.read()
                self.wfile.write(data)
        elif os.path.exists(path):
            self.send_response(200)
            if path.endswith('.css'):
                self.send_header('Content-type', 'text/css')
            elif path.endswith('.js'):
                self.send_header('Content-type', 'application/javascript')
            elif path.endswith('.jpg'):
                self.send_header('Content-type', 'image/jpeg')
            else:
                self.send_header('Content-type', 'text/html')
            self.end_headers()
            with open(path, 'rb') as file:
                self.wfile.write(file.read())
    def do_POST(self):
        path = self.path[1:]
        if path == 'delete_all_data':
            delete_all_data(self)
        elif path == 'save_parametres':
            save_parametres(self)
    def log_message(self, format, *args):
        return
def run_server():
    with socketserver.TCPServer(("", port), Handler) as httpd:
        print_with_lock(f"Serving at port {port}")
        httpd.serve_forever()



### ДЕТЕКТИРОВАНИЕ
##########################################################
def save_detection(image, detection):
    current_time = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
    image_name = "images/" + current_time + '.jng'
    with open(image_name, 'wb') as file:
        file.write(image)
    data = []
    with open("images_config.json", 'r', encoding='utf-8') as file:
        data = json.load(file)
    image_config = {}
    image_config['url'] = image_name
    image_config['description'] = detection
    data.insert(0, image_config)
    with open("images_config.json", 'w', encoding='utf-8') as file:
        json.dump(data, file, ensure_ascii=False, indent=4)
def detecting():
    global player, streaming_video, lastDetection
    while True:
        while not streaming_video:
            sleep(1)
        image = None
        with open("video_stream.jpg", 'rb') as file:
            image = file.read()
        base64_image = base64.b64encode(image).decode('utf-8')
        text_response = "Если на фото есть "
        parametres = []
        with open("parametres.json", 'r', encoding='utf-8') as file:
            parametres = json.load(file)
        for par in parametres:
            text_response += par + ", "
        text_response += ", то опиши это односложным предложением, иначе пришли только '0'"
        client = Mistral(api_key=api_key)
        try:
            chat_response = client.chat.complete(
                model= model,
                messages = [
                    {
                        "role": "user",
                        "content": [
                        {
                            "type": "text",
                            "text": text_response
                        },
                        {
                            "type": "image_url",
                            "image_url": f"data:image/jpeg;base64,{base64_image}" 
                        }
                        ]
                    }
                ]
            )
        except Exception as exception:
            print_with_lock('Ошибка при запросе к нейросети: ' + str(exception))
            sleep(2)
            detecting()
            return
            
        detection = chat_response.choices[0].message.content
        print_with_lock("Детекция: " + detection)
        if detection != '0' and detection != lastDetection:
            lastDetection = detection
            save_detection(image, detection)
            send_detection(image, detection)
        sleep(2)



### ВИДЕО ПОТОК
##########################################################
def streaming_images():
    global player
    while True:
        if not streaming_video:
            print_with_lock("стрим остановлен")
            return
        player.video_take_snapshot(0, "video_stream.jpg", 800, 600)
        sleep(1)
def on_media_state_changed(event):
    global streaming_video
    if event.type == vlc.EventType.MediaPlayerPlaying:
        print_with_lock("Видео поток успешно открыт")
        streaming_video = True
        stream_thread = threading.Thread(target=streaming_images)
        stream_thread.daemon = True
        stream_thread.start()
        print_with_lock("Стрим запущен")
        player.event_manager().event_detach(vlc.EventType.MediaPlayerPlaying)
    elif event.type == vlc.EventType.MediaPlayerStopped:
        print_with_lock("Не удалось покдлючиться к видео потоку, переподключение...")
        streaming_video = False
        connect_to_stream()
def connect_to_stream():
    global player
    print_with_lock("Подключение к видео потоку...")
    player = vlc.MediaPlayer("rtsp://192.168.1.16:8554/mjpeg/1")
    #rtsp://admin:admin@192.168.1.4:1935
    player.event_manager().event_attach(vlc.EventType.MediaPlayerPlaying, on_media_state_changed)
    player.event_manager().event_attach(vlc.EventType.MediaPlayerStopped, on_media_state_changed)
    player.play()
    sleep(10)
    if not player.is_playing():
        connect_to_stream()
        return

    
def print_with_lock(message):
    with thread_lock:
        print(message)
        
if __name__ == "__main__":
    server_thread = threading.Thread(target=run_server)
    server_thread.daemon = True
    server_thread.start()

    bot_thread = threading.Thread(target=run_telebot)
    bot_thread.daemon = True
    bot_thread.start()

    connect_to_stream()

    detecting()

    
