/*
* Copyright (c) 2006-2009 Erin Catto http://!www.box2d.org
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

#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"
namespace cs296
{/*!This is a constructor function which sets up the objects of rude-goldberg machine.*/
  dominos_t::dominos_t()
  {
    /*!##Ground
      ###b2EdgeShape shape;
        "shape" is an edge object which is a line segment representing ground.
        Its end points are (-90.0, 0.0) and (90.0, 0.0).\n
      ###b2BodyDef bd;
        "bd" is body definition and its position is set to default i.e. origin.
      ###b2Body * b1;
        "b1" is a pointer to rigid body object.

      "bd" is passed to world object to create the ground body "b1". By default bd is static body.
      Then CreateFixture function is called to set the shape and density of the "b1" object.
      Here its density is 0 and shape is of a line segment defined by "shape" variable.
    */
    b2Body* b1; 
    {
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
      
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f); 
    }
    

    
 
    /*!##Top horizontal shelf
      ###b2PolygonShape shape;
        "shape" is a polygon shape object which is a rectangle box object representing shelf for domino placement. 
        Its width is 12.0m and height is 0.5m.
      ###b2BodyDef bd;
        "bd" is body definition and its position is set to (-31.0,30.0) i.e the polygon will be centered a this position.
      ###b2Body* ground;
        "ground" is a pointer to rigid body object which is the horizontal shelf.
    
      This is the shelf on which dominos are placed.
      "bd" is passed to world object to create the pointer to rectangular shelf body which is saved in "ground" variable.
      By default "bd" is static body.
      Then CreateFixture function is called to set the shape and density of the "ground" object.
      Here its density is 0 and shape is of a polygon object defined by "shape" variable.
    */
    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);
	   
      b2BodyDef bd;
      bd.position.Set(-31.0f, 30.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    
    
    /*!##Dominos
      ###b2PolygonShape shape;
        "shape" is a polygon shape object which is a rectangular object representing the dominos. 
        Its width is 0.2m and height is 2m.
      ###b2FixtureDef fd;
        "fd" is a fixture definition whose shape is set by the above defined variable "shape" i.e a rectangle, density is set as 20 Kg/m^2 
        and friction coefficient is set as 0.1. 
      ###b2BodyDef bd;
        "bd" is body definition and its position is set inside the for loop to (-35.5 + 1.0 * i, 31.25), where "i" varies from 0 to 9.
        In each iteration a new polygon object (domino) is made. "bd" is a dynamic type object.  
      ###b2Body* body;
        "body" is a pointer to rigid body object which is a domino.
      
      After defining common fixture definitions, a for loop is used in which in each iteration 
      "bd" is passed to world object to create the pointer to a new domino object at a distance of 1m from the previous
      domino. This pointer is saved in "body" variable. 
      Then CreateFixture function is called to set fixtures of the "body" (domino) object using fixture definition of "fd".
      Finally it creates 10 dominos, starting from (-35.5 , 31.25) and every next domino at a distance of 1m in 
      horizontal with previous one.
    */
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
		
      for (int i = 0; i < 10; ++i)
    	{
    	  b2BodyDef bd;
    	  bd.type = b2_dynamicBody;
    	  bd.position.Set(-35.5f + 1.0f * i, 31.25f);
    	  b2Body* body = m_world->CreateBody(&bd);
    	  body->CreateFixture(&fd);
    	}
    }
      
    
    /*!##Another horizontal shelf
      ###b2PolygonShape shape;
        "shape" is a polygon shape object which is a rectangle box object representing shelf for spheres placement. 
        Its width is 14.0m, height is 0.5m, centre is (20.0,20.0) relative to (1.0,6.0) and angle with horizontal is 0.
      ###b2BodyDef bd;
        bd is body definition and its position is set to (1.0,6.0) .
      ###b2Body* ground;
        ground is a pointer to rigid body object which is the horizontal shelf.
      
      This is the shelf on which the last domino falls and pushes the train of spheres. 
      "bd" is passed to world object to create the pointer to rectangular shelf body which is saved in "ground" variable.
      By default "bd" is static body.
      Then CreateFixture function is called to set the shape and density of the "ground" object.
      Here its density is 0 and shape is of a polygon object defined by "shape" variable.
    */
    {
      b2PolygonShape shape;
      shape.SetAsBox(7.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
	
      b2BodyDef bd;
      bd.position.Set(1.0f, 6.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    //!##The pendulum that knocks the dominos off
    
    {

      /*!
        <I><B>Vertical Bar</B></I>
          ###b2PolygonShape shape;
            "shape" is a polygon shape object which is a rectangle box object representing the vertical bar . 
            Its width is 0.5m, height is 3m.
          ###b2BodyDef bd;
            bd is body definition and its position is set to (-36.5,28.0) .
          ###b2Body* b2;
            b2 is a pointer to rigid body object which is the vertical bar.

          "b2" is passed to world object to create the pointer to vertical body which is saved in "b2" variable.
          Then CreateFixture function is called to set the shape and density of the "b2" object.
          Here its density is 10.0 and shape is of a polygon object defined by "shape" variable.
      */
      b2Body* b2;
      {
      	b2PolygonShape shape;
      	shape.SetAsBox(0.25f, 1.5f);
      	  
      	b2BodyDef bd;
      	bd.position.Set(-36.5f, 28.0f);
      	b2 = m_world->CreateBody(&bd);
      	b2->CreateFixture(&shape, 10.0f);
      }
	     /*!
          <I><B>Pendulum Bob</B></I>
            ###b2PolygonShape shape;
              "shape" is a polygon shape object which is a rectangle box object representing the pendulum bob. 
              Its width is 0.5m, height is 0.5m.
            ###b2BodyDef bd;
              bd is body definition and its position is set to (-40.0,33.0) and its a dynamic object.
            ###b2Body* b4;
              b4 is a pointer to rigid body object which is the pendulum bob.
            ###b2RevoluteJointDef jd;
              "jd" is revolute joint definition, which forces two bodies to share a common hinge around which they can rotate.
            ###b2Vec2 anchor;
              "anchor" is a fixed point of type b2Vec2 common to both bodies needed by the revolute joint for the hinge. Its co-ordinates 
              are (-37.0, 40.0)

            "bd" is passed to world object to create the pointer to pendulum bob which is saved in "b4" variable.
            Then CreateFixture function is called to set the shape and density of the "b4" object.
            Here its density is 2.0 and shape is of a polygon object defined by "shape" variable.
            "jd" is initialised to vertical bar and pendulum bob object and one common point anchor. 
        */
      b2Body* b4;
      {
      	b2PolygonShape shape;
      	shape.SetAsBox(0.25f, 0.25f);
      	  
      	b2BodyDef bd;
      	bd.type = b2_dynamicBody;
      	bd.position.Set(-40.0f, 33.0f);
      	b4 = m_world->CreateBody(&bd);
      	b4->CreateFixture(&shape, 2.0f);
      }
	
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-37.0f, 40.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }
      
    
    /*!##The train of small spheres
        ###b2CircleShape circle;
          "circle" is a circular object of radius 0.5m. This is the size of a sphere present in the train of spheres.
        ###b2FixtureDef ballfd;
          "ballfd" is a fixture definition whose shape is set by the above defined variable "circle" i.e of a circle, 
          density is set as 1 Kg/m^2, friction and restitution coefficient are set as 0.0. 
        ###b2BodyDef ballbd;
          "ballbd" is body definition and its position is set inside the for loop to (-22.2 + 1.0 * i, 26.6), 
          where "i" varies from 0 to 9. In each iteration a new circular object (sphere) is made. "ballbd" is a dynamic type object.  
        ###b2Body* spherebody;
          "spherebody" is a pointer to rigid body object which is a sphere.
        
        After defining common fixture definitions, a for loop is used in which in each iteration 
        "ballbd" is passed to world object to create the pointer to a new sphere object at a distance of 1m from the previous
        body. This pointer is saved in "spherebody" variable. 
        Then CreateFixture function is called to set fixtures of the "spherebody" (sphere) object using fixture definition of "ballfd".
        Finally it creates 10 spheres, starting from (-22.2 , 26.6) and every next sphere at a distance of 1m in 
        horizontal with previous one.
    */
    {
      b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 0.5;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
	
      for (int i = 0; i < 10; ++i)
      	{
      	  b2BodyDef ballbd;
      	  ballbd.type = b2_dynamicBody;
      	  ballbd.position.Set(-22.2f + i*1.0, 26.6f);
      	  spherebody = m_world->CreateBody(&ballbd);
      	  spherebody->CreateFixture(&ballfd);
      	}
    }

    
    //!##The pulley system
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(-10,15);
      bd->fixedRotation = true;
      
      /*
        !<I><B>The open box</B></I>
          ###b2BodyDef *bd;
            bd is body definition whose position is set to (-10,15) and fixedRotation set to true which implies it can not be rotated.
          ###b2PolygonShape bs1, bs2, bs3;
            "bs1" is a horizontal rectangular object which is the base of the open box. "bs2" and "bs3" are the vertical rectangular object which form the side wall of the open box. 
            Their dimension is 4 x 0.4 and centres are (0,-1.9), (2.0,0.0) and (-2.0, 0.0) respectively and angle with the horizontal is 0 for all three.
          ###b2FixtureDef* fd1,fd2,fd3;
            These are the pointers to fixture definitions whose shape is set by the above defined variables "bs1", "bs2". "bs3" respectively, i.e a rectangle. 
            Density is set to 10 Kg/m^2, friction coefficient is 0.5 and restitution coefficient is 0.0.
          ###b2Body* box1;
            "box1" is a pointer to rigid body object which is the open box hanging on one side of the pulley.
          
          This is the box which goes down upon receiving train of spheres and lifts other side of pulley. 
          "bd" is passed to world object to create the pointer to rectangle box which is saved in "box1" variable.
          Then CreateFixture function is called to set fixtures of the "box1" (open box) object using fixture definition of 
          "fd1","fd2" and "fd3".This finally makes 3 rectangles(2 vertical and one horizontal) which makes open box.
      */

      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2, b2Vec2(-2.0f,0.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      //!<I><B>The bar</B></I>
      /*!### b2Body* box2;
       box2 is a pointer to rigid body object which is the horizontal bar attached to the right side of pulley.

       Here, position of the "bd" is changed to (10,15) and density of "fd1" is changed to 34 kg/m^2.
       "bd" is passed to world object to create the pointer to bar which is saved in "box2" variable.
       Then CreateFixture function is called to set fixtures of the "box2" (bar) object using fixture definition of "fd1".
      */
      bd->position.Set(10,15);	
      fd1->density = 34.0;	  
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);

      /*! 
        <I><B>The Pulley Joint</B></I>
          ###b2PulleyJointDef* myjoint;
            This is the pulley joint def. The pulley connects two bodies to ground and to each other.
          ###b2Vec2 worldAnchorOnBody1;
            This is Anchor point on body 1 in world axis which is set to (-10, 15).
          ###b2Vec2 worldAnchorOnBody2;
            This is Anchor point on body 2 in world axis which is set to (10, 15).
          ###b2Vec2 worldAnchorOnGround1;
            This is Anchor point on ground 1 in world axis which is set to (-10, 20).
          ###b2Vec2 worldAnchorOnGround1;
            This is Anchor point on ground 1 in world axis which is set to (10, 20).

          Now, pulley "myjoint" is initialised using two bodies, two ground anchors, two body anchors and ratio which is 1.0.
          Pulley contraints the motion of both the bodies such that total length is constant so when one goes up than other goes down and vice versa.
      */
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(-10, 15); 
      b2Vec2 worldAnchorOnBody2(10, 15); 
      b2Vec2 worldAnchorGround1(-10, 20);
      b2Vec2 worldAnchorGround2(10, 20);
      float32 ratio = 1.0f;
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }

    /*!##The revolving horizontal platform
      ###b2PolygonShape shape;
        "shape" is a polygon shape object which is a rectangle box object representing rotating platform. 
        Its width is 4.4m, height is 0.4m.
      ###b2BodyDef bd;
        bd is body definition and its position is set to (14.0,14.0) and is a dynamic body.
      ###b2FixtureDef fd;
        "fd" is a fixture definition whose shape is set by the above defined variable "shape" i.e of a rotating platform, 
        density is set as 1 Kg/m^2.
      ###b2Body* body;
        "body" is a pointer to rigid body object which is the rotating body.
      ###b2PolygonShape shape2;
        "shape" is a polygon shape object which is a rectangle box object representing static hinge for the rotating object.
        Its width is 0.4m, height is 0.4m.
      ###b2BodyDef bd2;
        "bd2" is body definition and its position is set to (14.0,16.0) and is a static body.
      ###b2RevoluteJointDef jointDef;
        "jointdef" is revolute joint definition, which forces two bodies to share a common hinge around which they can rotate.


      This is the rotating platform on which the heavy sphere is placed. 
      "bd" is passed to world object to create the pointer to horizontal platform which is saved in "body" variable.
      Then CreateFixture function is called to set fixtures of the "body" (rotating platform) object 
      using fixture definition of "fd".
      "bd2" is passed to world object to create the pointer to hidden hinge which is saved in "body2" variable.
      This is hidden because there is no fixture object for the body2 object.
      Now jointdef is intialised by two bodies which are "body" (rotating platform) and "body2" (hidden hinge)
      and anchor is set to (0,0) and collideConnect is set to false.

    */
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(14.0f, 14.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(14.0f, 16.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }

    /*!##The heavy sphere on the platform
      ###b2CircleShape circle;
        "circle" is a circular object of radius 1m. This is the size of the heavy sphere kept on the rotating platform. 
      ###b2FixtureDef ballfd;
        "ballfd" is a fixture definition whose shape is set by the above defined variable "circle" i.e of a circle, 
        density is set as 50 Kg/m^2, friction and restitution coefficient are set as 0.0. 
      ###b2BodyDef ballbd;
        "ballbd" is body definition whose position is set to (14.0,18.0) and type is set to dynamic body.
      ###b2Body* sbody;
        sbody is a pointer to rigid body object which is the heavy sphere.
      
      This is the sphere which falls from rotating platform on the see-saw. 
      "ballbd" is passed to world object to create the pointer to heavy sphere which is saved in "sbody" variable.
      Then CreateFixture function is called to set fixtures of the "sbody" (heavy sphere) object using fixture definition of "ballfd".
    */
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(14.0f, 18.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }

    //!##The see-saw system at the bottom

    {
      /*!
        <I><B>The triangle wedge</B></I>
          ###b2Vec2 vertices[3];
            It is an array of datatype b2Vec2, containing co-ordinates of the vertices in the x-y plane. 
            Its size is 3 and contains (-1,0), (1,0) and (0,1.5).
          ###b2PolygonShape poly;
            "poly" is a triangular shape object representing the wedge of the see-saw. Its vertices are set from the array "vertices"
            by calling the function "Set". 
          ###b2FixtureDef wedgefd;
            "wedgefd" is the pointer to a fixture definition whose shape is set by the above defined variable "poly" i.e a triangle, 
            density is set as 10 Kg/m^2, friction and restitution coefficient are set as 0.
          ###b2BodyDef wedgebd;
            "wedgebd" is body definition whose position is set as (30.0,0.0) and type is static body by default.
          ###b2Body* sbody;
            sbodybody is a pointer to rigid body object which is the triangular wedge of see-saw.
          
          This is the wedge on which a plank is attached.
          "wedgebd" is passed to world object to create the pointer to wedge which is saved in "sbody" variable.
          Then CreateFixture function is called to set fixtures of the "sbody" (wedge) object using fixture definition of "wedgefd".
     */
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(30.0f, 0.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      /*!<I><B>The plank on top of the wedge</B></I>
        ###b2PolygonShape shape;
          "shape" is a rectangular object representing the plank of the see-saw. Its width is 30m and height is 0.4m.
        ###b2BodyDef bd2;
          "bd2" is body definition whose position is set as (30.0,1.5.0) and type is set as dynamic body .
        ###b2Body* body;
          body is a pointer to rigid body object which is the plank of the see-saw.
        ###b2FixtureDef* fd2;
          "fd2" is the pointer to a fixture definition whose shape is set by the above defined variable "shape" i.e a rectangle and 
          density is set as 1 Kg/m^2.
        ###b2RevoluteJointDef jd;
          "jd" is revolute joint definition, which forces two bodies to share a common hinge around which they can rotate.
        ###b2Vec2 anchor;
          "anchor" is a fixed point of type b2Vec2 common to both bodies needed by the revolute joint for the hinge. Its co-ordinates 
          are (30.0, 1.5)
        
        This is the plank which is joint to the wedge object by revolute joint "jd".
        "bd2" is passed to world object to create the pointer to plank which is saved in "body" variable.
        Then CreateFixture function is called to set fixtures of the "body" (plank) object using fixture definition of "fd2".
        Now, "jd" joint is initialized with two bodies, "sbody" (wedge) and "body" (plank) and a common point "anchor". 
      */
      b2PolygonShape shape;
      shape.SetAsBox(15.0f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(30.0f, 1.5f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(30.0f, 1.5f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);

      /*!
        <I><B>The light box on the right side of the see-saw</B></I>
          ###b2PolygonShape shape2;
            "shape2" is a square shape object which is a light square box object representing box on the see-saw. 
            Its width is 4m, height is 4m.
          ###b2BodyDef bd3;
            "bd3" is body definition whose position is set as (40.0,2.0) and type is set as dynamic body .
          ###b2Body* body3;
            body3 is a pointer to rigid body object which is the light square box kept on see-saw.
          ###b2FixtureDef* fd3;
            "fd3" is the pointer to a fixture definition whose shape is set by the above defined variable "shape2" i.e a square and 
            density is set as 0.01 Kg/m^2.
          
          This is the square which is lifted when heavy sphere falls on the other side of see-saw. 
          "bd3" is passed to world object to create the pointer to square box which is saved in "body3" variable.
          Then CreateFixture function is called to set fixtures of the "body3" (light box) object using fixture definition of "fd3".
      */

      b2PolygonShape shape2;
      shape2.SetAsBox(2.0f, 2.0f);
      b2BodyDef bd3;
      bd3.position.Set(40.0f, 2.0f);
      bd3.type = b2_dynamicBody;
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 0.01f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
    }
  }
  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
