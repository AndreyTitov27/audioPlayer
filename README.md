# Audio Player
Audio Player is a simple and user-friendly desktop music player with YouTube / Youtube music searching, downloading and album cover integration features.
This player allows you to easily manage your playlists, download tracks, and listen to them within a single application.
And you can customize it however you want.

# Features
#### YouTube / Youtube Music Download: Paste a YouTube video link, and the player will automatically download and convert it to MP3.
#### Automatic Album Cover Integration: The player automatically adds album covers to downloaded tracks.
#### Playlist Management: Create, edit, and delete playlists, and add tracks to them.
#### Track Removal: Easily remove unwanted tracks from your playlist.
#### Simple and Intuitive Interface: The player features an easy-to-use interface that makes navigating the main features straightforward.

# Usage
Downloading Music: Paste a YouTube video / Youtube music link and choose a directory to save the track. Than add it to playlist you want.
Searching Music: Type a query and select the track to start downloading track.
Managing Playlists: You can add and remove tracks, create new playlists, and manage the current playback.
Album Covers: The player automatically adds album covers to downloaded tracks if available.

## Tech Stack
Programming Language: C++  
Framework: Qt
 - QtWidgets: For building the user interface components.  
 - QtMultimedia: For handling audio playback.  
 - Media Player: QMediaPlayer (from QtMultimedia) for playing audio files.  
 - Drag-and-Drop: Custom drag-and-drop implementation for managing playlist items.
  
YouTube Integration: Functionality to download tracks via YouTube links written with Python and built to .exe.  
Development Environment: Visual Studio  
Build System: CMake  
Compiler: MSVC

## Contributing
If you have ideas or suggestions for improving the player, feel free to open an issue or submit a pull request.

## License
This project is licensed under the GPL 3.0 License. See the LICENSE file for details.
