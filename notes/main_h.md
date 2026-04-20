[[DeathRow Client]]

### Imports
application_h
[[event_handler_h]]
[[application_h]]

### Functions
- Initialize SLD2
- main

### Working
##### Initialize SLD2
if SLD2 is not initialized then it initializes it and return.

##### main
inside an infinite loop performs the following task
- calls initialize function
- calculates delta
- handle input events
- updates
- render to screen
- FPS management
if loop exits, cleanly exit the application