/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */


#ifndef _CS296BASE_HPP_
#define _CS296BASE_HPP_

#include "render.hpp"
#include <Box2D/Box2D.h>
#include <cstdlib>

#define	RAND_LIMIT 32767

namespace cs296
{

  //! What is the difference between a class and a struct in C++?
  /*!
  Members of class are private by default whereras that of structs are public.Similarly inheritance is also private in classes and public in structs.
  */
  class base_sim_t;
  struct settings_t;
  
  //! Why do we use a typedef
  typedef base_sim_t* sim_create_fcn(); 
  //! \struct settings_t 
  //!  This is the struct which contains the settings that are supposed to be displayed on the user interface and are used in
  //! testing of simulation. It initiates each parameter to some value and display thinngs on the screen according to the values 
  //! of the parameter that are under control of uesr.
  struct settings_t
  {
    //! Notice the initialization of the class members in the constructor.
    //!How is this happening? 
    //! It is the constructor for struct settings_t.
    //! It is a way of initialising struct members where value of each member is set to the value inside parenthesis.
    settings_t() :
      view_center(0.0f, 20.0f),
      hz(60.0f),
      velocity_iterations(8),
      position_iterations(3),
      draw_shapes(1),
      draw_joints(1),
      draw_AABBs(0),
      draw_pairs(0),
      draw_contact_points(0),
      draw_contact_normals(0),
      draw_contact_forces(0),
      draw_friction_forces(0),
      draw_COMs(0),
      draw_stats(0),
      draw_profile(0),
      enable_warm_starting(1),
      enable_continuous(1),
      enable_sub_stepping(0),
      pause(0),
      single_step(0)
    {}
    //! variable to set the center of the screen its a b2Vec2 type contains a x,y coordinate.
    b2Vec2 view_center;
    //! variable to set the simulation steps per frame it is float32 type of variable
    float32 hz;
    //! variable to set velocity iterations in the simulation it is an int32 typr.
    int32 velocity_iterations;
    //! variable to set position iterations in the simulation it is an int32 type.
    int32 position_iterations;
    //! variable to set drawing of shape to true or false if true than will draw shapes otherwise not. 
    //!It is an int32 type object.
    int32 draw_shapes;
    //! variable to set drawing of joint wires to true or false if true than will draw joins otherwise not. 
    //!It is an int32 type object.
    int32 draw_joints;
    //! variable to set drawing of border around shapes to true or false if true than will draw border around shapes otherwise not. 
    //!It is an int32 type object.
    int32 draw_AABBs;
    //!variable to set d
    //!It is an int32 type object.
    int32 draw_pairs;
    //! variable to set drawing of contact points to true or false
    //!It is an int32 type object.
    int32 draw_contact_points;
    //! variable to set drawing of contact normals to true or false
    //!It is an int32 type object.
    int32 draw_contact_normals;
    //! variable to set drawing of contact forces to true or false
    //!It is an int32 type object.
    int32 draw_contact_forces;
    //! variable to set drawing of friction forces to true or false
    //!It is an int32 type object.
    int32 draw_friction_forces;
    //! variable to set drawing of center of mass to true or false
    //!It is an int32 type object.
    int32 draw_COMs;
    //! variable to set to show stats to true or false if true it shows stats on gui
    //!It is an int32 type object.
    int32 draw_stats;
    //! variable to set to show profile to true or false if true it shows profile of objects on gui
    //!It is an int32 type object.
    int32 draw_profile;
    //! variable to Enable/disable warm starting.
    //!It is an int32 type object.
    int32 enable_warm_starting;
    //! variable to Enable/disable continuous physics.
    //!It is an int32 type object.
    int32 enable_continuous;
    //! variable to Enable/disable single stepped continuous physics
    //!It is an int32 type object.
    int32 enable_sub_stepping;
    //! variable to pause the simulation
    //!It is an int32 type object.
    int32 pause;
    //! variable to enable single step by step simulation
    //!It is an int32 type object.
    int32 single_step;
  };
  //! \struct sim_t 
  //! It is a struct which contains an instance of class base_sim_t and a name corresponding to simulation.
  struct sim_t
  {
    const char *name;//!< It is the name that will e given to the simulatin
    sim_create_fcn *create_fcn; //!< it is a variable of tpe base_sim_t
    
    //! This is a constructor for struct sim_t which takes name string, and a base_sim_t type objects and initiates the members of struct accordingly.
    sim_t(const char *_name, sim_create_fcn *_create_fcn): 
      name(_name), create_fcn(_create_fcn) {;}
  };
  
  extern sim_t *sim;
  
  
  const int32 k_max_contact_points = 2048;  

  //! \struct contact_point_t 
  //! This is the struct which contains information of contact point of two bodies during simulation. Whenever draw_contact_points 
  //! is set to true , it should draw contact points, normals, tangents on GUI.
  struct contact_point_t
  {
    b2Fixture* fixtureA;//!< It is a fixture type object which contains informatin about density, shape, friction etc. 
    b2Fixture* fixtureB;//!< It is a fixture type object which contains informatin about density, shape, friction etc.
    b2Vec2 normal;//!< This is a vector corresponding to the normal of contact points
    b2Vec2 position;//!< This is the position of contact point
    b2PointState state;//!< contains information about state of contact point
  };
  


  //!This is a derived class of b2ContactListener. This class is implemented to get the contact 
  //!results by traversing the contact lists after the time step.
  class base_sim_t : public b2ContactListener
  {
  public:
    /*!\fn base_sim_t()
      \brief It is the constructor of the base_sim_t class.
    */
    base_sim_t();

    //! Virtual destructors - amazing objects. Why are these necessary?
    /*!
    Virtual destructors are useful when we have to delete an instance of a derived class through a pointer to base class
    it is used here so that when we have pointer of base class that is b2ContactListener we can delete instance of derived
    class base_sim_t.
    */
    virtual ~base_sim_t();
    

    /*!\fn void set_text_line(int32 line)
       \brief sets the m_text_line attribute to the sent value
       \param line a int32 datatype
       \return void
     */
    void set_text_line(int32 line) { m_text_line = line; }

    /*!\fn void draw_title(int32 line)
       \brief sets the x, y coordinates of title and sets the string corresponding to title and draws string on GUI
       \param int x x coordinate of title
       \param int y y coordinate of title
       \param char* string title string
       \return void
     */
    void draw_title(int x, int y, const char *string);
    
    /*!\fn void step(settings_t* settings)
      \brief this function updates the simulation at every step and does necessary changes in the simulation
      \param settings_t* settings contains information about user settings for simulation and test conditions
      \return void
    */
    virtual void step(settings_t* settings);

    /*!\fn void keyboard(unsigned char key)
       \brief to avoid the warnings of not using variable corresponding to the char key on keyboard press
       \param unsigned char key key pressed on keyboard
       \return void
     */
    virtual void keyboard(unsigned char key) { B2_NOT_USED(key); }
    /*!\fn void keyboard_up(unsigned char key)
       \brief to avoid the warnings of not using variable corresponding to the char key on keybord key release
       \param unsigned char key  key released on keyboard
       \return void
     */
    virtual void keyboard_up(unsigned char key) { B2_NOT_USED(key); }

    /*!\fn void shift_mouse_down(const b2Vec2& p)
       \brief to avoid the warnings of not using variable corresponding to the b2vec2 p on mouse shift click
       \param b2Vec2& p position of mouse shift click
       \return void
     */
    void shift_mouse_down(const b2Vec2& p) { B2_NOT_USED(p); }
    /*!\fn void mouse_down(const b2Vec2& p)
       \brief to avoid the warnings of not using variable corresponding to the b2vec2 p on mouse click
       \param b2Vec2& p position of mouse click
       \return void
     */
    virtual void mouse_down(const b2Vec2& p) { B2_NOT_USED(p); }
    /*!\fn void mouse_up(const b2Vec2& p)
       \brief to avoid the warnings of not using variable corresponding to the b2vec2 p on mouse click up
       \param b2Vec2& p position of mouse click up
       \return void
     */
    virtual void mouse_up(const b2Vec2& p) { B2_NOT_USED(p); }

     /*!\fn void mouse_move(const b2Vec2& p)
       \brief to avoid the warnings of not using variable corresponding to the b2vec2 p on mouse motion
       \param b2Vec2& p position of mouse motion
       \return void
     */
    void mouse_move(const b2Vec2& p) { B2_NOT_USED(p); }

     /*!\fn void joint_destroyed(const b2Joint* joint)
       \brief Let derived tests know that a joint was destroyed. to avoid the warnings of not using variable corresponding to the destroyed joint
       \param b2Joint* joint information of the destroyed joint
       \return void
     */
    virtual void joint_destroyed(b2Joint* joint) { B2_NOT_USED(joint); }
    
    /*!\fn void begin_contact(b2Contact* contact)
       \brief To know if contact begun and to avoid the warnings of not using variable corresponding to the begining of contact
       \param b2Contact *contact information about new contact made between bodies
       \return void
     */
    virtual void begin_contact(b2Contact* contact) { B2_NOT_USED(contact); }
    /*!\fn void end_contact(b2Contact* contact)
       \brief To know if contact ends and to avoid the warnings of not using variable corresponding to the ending of contact
       \param b2Contact* contact information at end of contact between bodies
       \return void
     */
    virtual void end_contact(b2Contact* contact) { B2_NOT_USED(contact); }
    /*!\fn void pre_solve(b2Contact* contact, const b2Manifold* oldManifold)
       \brief based on pre contact conditions finds the possible contact points and saves their information according to struct
       \param b2Contact* contact information of two bodies in simulation
       \param b2Manifold* oldManifold it contains information of contact points and normal vectors.
       \return void
     */
    virtual void pre_solve(b2Contact* contact, const b2Manifold* oldManifold);
    /*!\fn void post_solve(const b2Contact* contact, const b2ContactImpulse* impulse)
       \brief To gather collision impulse events. It is avoiding the warnings of not using variable corresponding to the impulsive collision
       \param b2Contact* contact information at end of contact between bodies after collision
       \param b2ContactImpulse* impulse impulse information after collision
       \return void
     */
    virtual void post_solve(const b2Contact* contact, const b2ContactImpulse* impulse)
    {
      B2_NOT_USED(contact);
      B2_NOT_USED(impulse);
    }

  //!How are protected members different from private memebers of a class in C++ ?
  //! private members are only available to class's members but protected members are also available to inherited classes.
  protected:

    //! What are Friend classes?
    //! Friend class object can use both protected and private members of a class and help in improving encapsulation
    friend class contact_listener_t;
    
    b2Body* m_ground_body; //!< b2Body object corresponding to ground object
    b2AABB m_world_AABB;  //!< creates the bounding boxes for shapes in GUI
    contact_point_t m_points[k_max_contact_points];  //!< array to contain all the contact points this is created during pre_solve functions call
    int32 m_point_count; //!< keep counts of corrent contact points, calculated in pre_solve

    debug_draw_t m_debug_draw; //!< debug draw to draw the shapes of the debuggin part of the world like drawing normal, tangents etc.
    int32 m_text_line; //!< to keep track of y position of text printed on the screen
    b2World* m_world; //!< world object for the simulation contains all the shapes, joints etc.

    int32 m_step_count;//!<keeps count of number of steps in simulation
    
    b2Profile m_max_profile; //!< it is used to for profiling data on screen, keeps curent profile
    b2Profile m_total_profile; //!< it is used to for profiling data on screen, keeps total profile
  };
}

#endif
