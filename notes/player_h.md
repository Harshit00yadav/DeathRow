contains important structs that defines player behavior and controls

---
### Imports 
- SDL2_image
- [[camera_h]]

### Structs
##### Controller
- bool right
- bool left
- bool up
- bool down
- bool orientation
- int x
- int y

##### Player
- int id
- int x
- int y
- char state
- bool state_change
- int tile_size
- int frame_index
- int frame_count
- int animation_index
- int orientation
- double cumilative_delta
- SDL_Texture * spritesheet
- bool isrendered

