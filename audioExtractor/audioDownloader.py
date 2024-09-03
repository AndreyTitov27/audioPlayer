from pytube import YouTube
from ytmusicapi import YTMusic
import subprocess
import requests
import os
import sys
import socket
from mutagen.mp3 import MP3
from mutagen.id3 import ID3, APIC, TIT2, TPE1, TDRC, error

def get_directory_path(directory_name):
    if getattr(sys, 'frozen', False):
        application_path = os.path.dirname(sys.executable)
    else:
        application_path = os.path.dirname(os.path.abspath(__file__))
    
    return os.path.join(application_path, directory_name)

def get_ffmpeg_path():
    if getattr(sys, 'frozen', False):
        return os.path.join(sys._MEIPASS, 'ffmpeg.exe')
    else:
        return os.path.join('ffmpeg', 'ffmpeg.exe')

def is_connected():
    try:
        # Попытка соединения с Google DNS
        socket.create_connection(("8.8.8.8", 53))
        return True
    except OSError:
        return False

def to_youtube_music(_text):
    ytData = YouTube(_text)
    _title = ytData.title
    _author = ytData.author
    ytmusic = YTMusic()
    search_request = f"{_author} {_title}"
    search_result = ytmusic.search(search_request, filter='songs')
    link = None

    for result in search_result:
        if result['title'] == _title:
            print("search completed")
            link = f"https://music.youtube.com/watch?v={result['videoId']}"
            return link

    return _text

def download_cover(url, save_path):
    response = requests.get(url)
    if response.status_code == 200:
        with open(save_path, 'wb') as file:
            file.write(response.content)
        return True
    return False

def add_cover_to_mp3(mp3_path, cover_path, title, artist):
    audio = MP3(mp3_path, ID3=ID3)
    try:
        audio.add_tags()
    except error:
        pass

    audio.tags.version = (2, 3, 0)
    
    with open(cover_path, 'rb') as img:
        audio.tags.add(
            APIC(
                encoding=3,
                mime='image/jpeg',
                type=3,
                desc='Cover',
                data=img.read()
            )
        )
    
    audio.tags.add(
        TIT2(encoding=3, text=title)
    )
    audio.tags.add(
        TPE1(encoding=3, text=artist)
    )
    
    audio.save(v2_version=3)

def run_ffmpeg(input_url, output_file):
    ffmpeg_path = get_ffmpeg_path()

    cmd = [
        ffmpeg_path,
        '-i', input_url,
        '-f', 'mp3',
        '-ab', '320k',
        '-acodec', 'libmp3lame',
        output_file
    ]
    
    process = subprocess.Popen(
        cmd,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        creationflags=subprocess.CREATE_NO_WINDOW
    )
    
    audio_data, err = process.communicate()
    
    if process.returncode != 0:
        print("Error:", err.decode())

def main():
    input_file_path = get_directory_path('input.txt')
    tracks_directory = get_directory_path('tracks')

    if not is_connected():
        print("No internet connection.")
        return
    
    if not os.path.exists(input_file_path):
        with open('input.txt', 'w') as file:
            pass
        return
    
    with open(input_file_path, 'r') as file:
        text = file.readline().strip()

    yt = None
    if text.startswith("https://www.youtube.com") or text.startswith("https://youtu.be"):
       yt = YouTube(to_youtube_music(text))
    else:
        yt = YouTube(text)
    title = yt.title
    author = yt.author

    download_folder = tracks_directory
    if not os.path.exists(download_folder):
        os.makedirs(download_folder)

    mp3_filename = os.path.join(download_folder, f"{author} - {title}.mp3")
    cover_path = os.path.join(download_folder, 'cover.jpg')

    thumbnail_url = yt.thumbnail_url

    if not download_cover(thumbnail_url, cover_path):
        return

    stream_url = yt.streams.first().url
    
    run_ffmpeg(stream_url, mp3_filename)

    add_cover_to_mp3(mp3_filename, cover_path, title, author)

    if os.path.exists(cover_path):
        os.remove(cover_path)

if __name__ == "__main__":
    main()
