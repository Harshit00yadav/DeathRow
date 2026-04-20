### Imports 
- [[client_h]]
- [[player_h]]
- [[camera_h]]

---
### App Struct
- int ID
- SDL_Window * window;
- SDL_Renderer * renderer;
- char * server_response;
- UDPcon conn
- pthread_t listener_thread_id
- int mouseX
- int mouseY
- Node * map
- SDL_Texture ** textures
- int ntextures
- Playerll * allplayers
- Controller controller
- Camera cam

---
### Functions
- sdl_init
- app_cleanup
- update
- render