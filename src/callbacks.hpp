/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */

//! Notice the use of these pre-processor directives on top of each header file
//! Why are they used?
//! These are Include guards. It is used to prevent double declaration of any identifiers such as types, enums and satic variables. If header file is not included earlier it defines it and continues otherwise if it was included earlier, ifndef fails and doesn't reinclude it.

#ifndef _CALLBACKS_HPP_
#define _CALLBACKS_HPP_

/*! 
  This file defines all the callback functions our code needs.
  Why are they not members of a class? Can you make them into a class?
	
	Here member function of the class are static, it means no matter how many objects of the class are created, there is only one copy of the 	static member. It is shared by all objects of the class, and by declaring it static, we make it independent of any particular object of the class. A static member function can be called even if no objects of the class exist. So, these can be treated as not a member of the class. 
	No, we can not make them into a class. If we do it then for every instance of the class, a copy of the same function will exist for each object resulting in the multiple copies of that function. So for every instance of class these functions will be called simultaneously corresponding to a event (like pressing a key). And it is not possible, as simultaneously more than one function can not be called. 


  Callback functions are called when a event occurs due to the press
  of a key, mouse button, or a GUI element like a menu item is
  clicked or scroller is dragged. Some callbacks are triggered after
  a fixed intervals when a timer elapses.  
*/

//! These are user defined include files
//! Included in double quotes - the path to find these has to be given at compile time
#include "render.hpp"
#include "cs296_base.hpp"

namespace cs296
{
  class callbacks_t
  {
  public:
  //! Helper function for coordinates system conversion
  //! Note the function is a static function. Read about C++ static functions
  static b2Vec2 convert_screen_to_world(int32 x, int32 y);
  
  //! GLUT resize callback. This is set via GLUI. Why is this so?
	//! This function is called when window is resized. Parameters passed to this function are current window height and current window width.

  //! This gets called when the window is resized. Passed as parameters
  //! are the current window width and height.
  static void resize_cb(int32 w, int32 h);
  
  //! GLUT keyboard callback
  //! This gets called whenever a key is pressed
  static void keyboard_cb(unsigned char key, int x, int y);
  
  //! GLUT keyboard callback for keys with special keycodes
  static void keyboard_special_cb(int key, int x, int y);
  
  //! Another keyboard callback? Why is this necessary? Is this used?
	//! Another keyboard callback is used because we have not specified what to do if keyboard key is released. It is necessary because it is a different event than from pressing the key, and if it is not called then the effect which occured after pressing a key can't be undone. Like if a key magnifies the screen then it should stop magnifying it when that key is released. So this function will tell it to stop magnifying as the key is released. Yes It is used when the key is released.
  static void keyboard_up_cb(unsigned char key, int x, int y);
  
  //! GLUT mouse callback
  //! This is called when a mouse button is pressed
  static void mouse_cb(int32 button, int32 state, int32 x, int32 y);
  
  //! GLUT Mouse motion callback
  //! This is called when the mouse is moved/dragged
  static void mouse_motion_cb(int32 x, int32 y);
  
  //! GLUT timer callback.
  //! This is used to control the frame rate - figure out how by reading the GLUT manual.
  static void timer_cb(int);
  
  //! GLUT display callback
  //! This draws every time a draw event is posted. 
  //! It also xecutes the main simulation loop by calling test->step(...)
  static void display_cb(void);
  
  //! GLUI callback - Called when the restart button is pressed
  static void restart_cb(int);
  
  //! GLUI callback - Called when the pause button is pressed
  static void pause_cb(int);
  
  //! GLUI callback - Called when the single-step button is pressed
  static void single_step_cb(int);
  
  //! GLUI callback - Called when the exit button is pressed
  static void exit_cb(int code);
  };
};

#endif
