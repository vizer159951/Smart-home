document.querySelectorAll('.sidebar ul li').forEach(item => {
    item.addEventListener('click', event => {
        document.querySelectorAll('.settings-window').forEach(window => {
            window.classList.remove('active');
        });
        const target = event.currentTarget.getAttribute('data-target');
        document.getElementById(target).classList.add('active');
        document.getElementById('save-button').style.display = 'none';

        stopVideoStream();

        if (target === 'archive') {
            fetchImages();
        } else if (target === 'video-stream') {
            startVideoStream();
        } else if (target === 'settings') {
            fetchSettings();
        }
    });
});

document.getElementById('delete-button').addEventListener('click', () => {
    if (confirm('Вы точно хотите удалить все данные?')) {
        deleteAllData();
    }
});

document.getElementById('add-button').addEventListener('click', () => {
    addSetting();
    document.getElementById('save-button').style.display = 'inline-block';
});

document.getElementById('save-button').addEventListener('click', () => {
    saveSettings();
});

async function fetchImages() {
    try {
        const response = await fetch('images_config.json');
        const images = await response.json();
        displayImages(images);
    } catch (error) {
        console.error('Error fetching images:', error);
    }
}

function displayImages(images) {
    const grid = document.getElementById('archive-grid');
    grid.innerHTML = '';
    images.forEach(image => {
        const container = document.createElement('div');
        container.classList.add('image-container');

        const img = document.createElement('img');
        img.src = image.url;
        img.alt = image.description;
        img.addEventListener('click', () => openPopup(image.url));
        container.appendChild(img);

        const desc = document.createElement('p');
        desc.textContent = image.description;
        container.appendChild(desc);

        grid.appendChild(container);
    });
}

function openPopup(imageUrl) {
    const popup = document.getElementById('image-popup');
    const popupImage = document.getElementById('popup-image');
    popupImage.src = imageUrl;
    popup.style.display = 'flex';
    popupImage.addEventListener('click', closePopup);
}

function closePopup() {
    const popup = document.getElementById('image-popup');
    popup.style.display = 'none';
    const popupImage = document.getElementById('popup-image');
    popupImage.removeEventListener('click', closePopup);
}

let videoStreamInterval;

async function startVideoStream() {
    const videoStream = document.getElementById('video-stream');
    const img = document.createElement('img');
    img.classList.add('video-stream-img');
    videoStream.appendChild(img);

    async function updateImage() {
        try {
            const response = await fetch('video_stream.jpg');
            const blob = await response.blob();
            const url = URL.createObjectURL(blob);
            img.src = url;
        } catch (error) {
            console.error('Error fetching video stream:', error);
        }
    }

    updateImage();
    videoStreamInterval = setInterval(updateImage, 1000);
}

function stopVideoStream() {
    clearInterval(videoStreamInterval);
    const videoStream = document.getElementById('video-stream');
    const img = videoStream.querySelector('.video-stream-img');
    if (img) {
        videoStream.removeChild(img);
    }
}

async function deleteAllData() {
    try {
        const response = await fetch('/delete_all_data', { method: 'POST' });
        if (response.ok) {
            fetchImages();
        } else {
            console.error('Error deleting data:', response.statusText);
        }
    } catch (error) {
        console.error('Error deleting data:', error);
    }
}

async function fetchSettings() {
    try {
        const response = await fetch('parametres.json');
        const settings = await response.json();
        displaySettings(settings);
    } catch (error) {
        console.error('Error fetching settings:', error);
    }
}

function displaySettings(settings) {
    const list = document.getElementById('settings-list');
    list.innerHTML = '';
    settings.forEach(setting => {
        const li = document.createElement('li');
        const input = document.createElement('input');
        input.type = 'text';
        input.value = setting;
        input.placeholder = 'Setting';
        const button = document.createElement('button');
        button.textContent = 'Delete';
        button.addEventListener('click', () => {
            document.getElementById('save-button').style.display = 'inline-block';
            list.removeChild(li);
        });
        li.appendChild(input);
        li.appendChild(button);
        list.appendChild(li);
    });
}

function addSetting() {
    const list = document.getElementById('settings-list');
    const li = document.createElement('li');
    const input = document.createElement('input');
    input.type = 'text';
    input.placeholder = 'New setting';
    const button = document.createElement('button');
    button.textContent = 'Delete';
    button.addEventListener('click', () => {
        document.getElementById('save-button').style.display = 'inline-block';
        list.removeChild(li);
    });
    li.appendChild(input);
    li.appendChild(button);
    list.appendChild(li);
}

async function saveSettings() {
    const list = document.getElementById('settings-list');
    const settings = Array.from(list.querySelectorAll('input')).map(input => input.value);

    try {
        const response = await fetch('save_parametres', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(settings)
        });

        if (response.ok) {
            document.getElementById('save-button').style.display = 'none';
        } else {
            console.error('Error saving settings:', response.statusText);
        }
    } catch (error) {
        console.error('Error saving settings:', error);
    }
}