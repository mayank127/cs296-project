

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
 * Base code for CS 296 Software Systems Lab from divyam
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */
//Mayank
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
    
  	//Pendulum
//!##The pendulum that kicks the first ball kept on horizontal bar
/*!
        <I><B>Vertical Bar</B></I>
          ###b2PolygonShape shape;
            "shape" is a polygon shape object which is a square box object representing the vertical bar . 
            Its width is 0.25m, height is 0.25m.
          ###b2BodyDef bd;
            bd is body definition and its position is set to (-30.5,36.0) .
          ###b2Body* b2;
            b2 is a pointer to rigid body object which is the vertical bar.

          "b2" is passed to world object to create the pointer to vertical body which is saved in "b2" variable.
          Then CreateFixture function is called to set the shape and density of the "b2" object.
          Here its density is 10.0 and shape is of a polygon object defined by "shape" variable.
      */

/*!
          <I><B>Pendulum Bob</B></I>
            ###b2PolygonShape shape;
              "shape" is a polygon shape object which is a rectangle box object representing the pendulum bob. 
              Its width is 0.4m, height is 0.5m.
            ###b2BodyDef bd;
              bd is body definition and its position is set to (-25.0,33.0) and its a dynamic object.
            ###b2Body* b4;
              b4 is a pointer to rigid body object which is the pendulum bob.
            ###b2RevoluteJointDef jd;
              "jd" is revolute joint definition, which forces two bodies to share a common hinge around which they can rotate.
            ###b2Vec2 anchor;
              "anchor" is a fixed point of type b2Vec2 common to both bodies needed by the revolute joint for the hinge. Its co-ordinates 
              are (-30.5, 40.0)

            "bd" is passed to world object to create the pointer to pendulum bob which is saved in "b4" variable.
            Then CreateFixture function is called to set the shape and density of the "b4" object.
            Here its density is 100.0 and shape is of a polygon object defined by "shape" variable.
            "jd" is initialised to vertical bar and pendulum bob object and one common point anchor. 
        */
    {
      b2Body* b2;
      {
      	b2PolygonShape shape;
      	shape.SetAsBox(0.25f, 0.25f);
      	  
      	b2BodyDef bd;
      	bd.position.Set(-30.5f, 36.0f);
      	b2 = m_world->CreateBody(&bd);
      	b2->CreateFixture(&shape, 10.0f);
      }
      b2Body* b4;
      {
      	b2PolygonShape shape;
      	shape.SetAsBox(0.4f, 0.5f);

      	b2FixtureDef ballfd;
	      ballfd.shape = &shape;
	      ballfd.density = 100.0f;
	      ballfd.friction = 0.0f;
	      ballfd.restitution = 0.0f;
	      b2BodyDef ballbd;
	      ballbd.type = b2_dynamicBody;
	      ballbd.position.Set(-25.0f, 33.0f);
	      b4 = m_world->CreateBody(&ballbd);
	      b4->CreateFixture(&ballfd);
      }
	
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-30.5f, 40.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }

    //platforms
//!##Horizontal Platforms with attached vertical bars
	/*!<I><B>Horizontal Bars</B></I>
      ###b2PolygonShape shape;
        "shape" is a polygon shape object which is a rectangle box object representing shelf for spheres placement. 
        Its width is 3.50m, height is 0.25m.
      ###b2BodyDef bd;
        bd is body definition  .
      ###b2Body* ground;
        ground is a pointer to rigid body object which is the horizontal shelf.
      
      These are the four platform on which spheres are kept and they start moving upon being hit by some other object.
      Position for each platform is -36.0 f as x- cordinate and they are kept at a distance of 4 m in vertical.
      So by running in it loop 4 such bars are created.
      "bd" is passed to world object to create the pointer to rectangular shelf body which is saved in "ground" variable.
      By default "bd" is static body.
      Then CreateFixture function is called to set the shape and density of the "ground" object.
      Here its density is 0 and shape is of a polygon object defined by "shape" variable.
    */
    /*!<I><B>Vertical Bars</B></I>
      ###b2PolygonShape shape;
        "shape" is a polygon shape object which is a rectangle box object representing shelf for spheres placement. 
        Its width is 0.2m, height is 1.6m.
      ###b2BodyDef bd1;
        bd1 is body definition  .
      ###b2Body* body;
        body is a pointer to rigid body object which is the vertical bar.
      ###b2FixtureDef *fd;
		this variable will store the properties of the vertical bar.
		###b2RevoluteJointDef jointDef;
		 this variable is for the joint between vertical bar and horizontal bar.
      
      
      These are the four bars which are hinged with the vertical bar, and they start rotating as soon as hit by a ball.
      Position for each platform is at the corner of horizontal bar.
      So by running in it loop 4 such bars are created.
      "bd" is passed to world object to create the pointer to rectangular shelf body which is saved in "ground" variable.
      By default "bd1" is static body.
      Then CreateFixture function is called to set the shape and density of the "body" object.
      Here its density is 50 and shape is of a polygon object defined by "shape" variable.
      Position is set for both the anchors point respective to bodies.
    */
    
    
	  {
			b2PolygonShape shape;
			shape.SetAsBox(3.5f, 0.25f);
			for(int i=0;i<4;i++){
				b2BodyDef bd;
				bd.position.Set(-36.0f, 30.0f - i*4.0f);
				b2Body* ground = m_world->CreateBody(&bd);
				ground->CreateFixture(&shape, 0.0f);

				b2PolygonShape shape;
				shape.SetAsBox(0.2f, 1.6f);
				float pos =-39.5f, a=-3.5f; 
				if(i%2==1){ pos=-32.5f; a =3.5f;}
				b2BodyDef bd1;
				bd1.position.Set(pos, 32.0f - i*4.0f);
				bd1.type = b2_dynamicBody;
				b2Body* body = m_world->CreateBody(&bd1);
				b2FixtureDef *fd = new b2FixtureDef;
				fd->density = 50.0f;
				fd->shape = new b2PolygonShape;
				fd->shape = &shape;
				body->CreateFixture(fd);

				b2RevoluteJointDef jointDef;
				jointDef.bodyA = body;
				jointDef.bodyB = ground;
				jointDef.localAnchorA.Set(0,-1.6f);
				jointDef.localAnchorB.Set(a,0);
				jointDef.collideConnected = false;
				m_world->CreateJoint(&jointDef);
			}
	  }


	  //balls
	   /*!##Balls kept on horizontal platform
        ###b2CircleShape circle;
          "circle" is a circular object of radius 1m. This is the size of a sphere present on the platform.
        ###b2FixtureDef ballfd;
          "ballfd" is a fixture definition whose shape is set by the above defined variable "circle" i.e of a circle, 
          density is set as 5 Kg/m^2, friction and restitution coefficient are set as 0.0. 
        ###b2BodyDef ballbd;
          "ballbd" is body definition and its position is set inside the for loop , 
          where "i" varies from 0 to 4. In each iteration a new circular object (sphere) is made. "ballbd" is a dynamic type object.  
        ###b2Body* sbody;
          "sbody" is a pointer to rigid body object which is a sphere.
        
        After defining common fixture definitions, a for loop is used in which in each iteration 
        "ballbd" is passed to world object to create the pointer to a new sphere object at a distance of 4m from the previous
        body. This pointer is saved in "spherebody" variable. 
        Then CreateFixture function is called to set fixtures of the "sbody" (sphere) object using fixture definition of "ballfd".
        Finally it creates 4 spheres.
    */
	  {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
			
			for(int i=0;i<4;i++){
				float pos =-33.0;
				if(i%2==1)pos=-39.0;
	      b2FixtureDef ballfd;
	      ballfd.shape = &circle;
	      ballfd.density = 5.0f;
	      ballfd.friction = 0.0f;
	      ballfd.restitution = 0.0f;
	      b2BodyDef ballbd;
	      ballbd.type = b2_dynamicBody;
	      ballbd.position.Set(pos, 33.0f - i*4.0f);
	      sbody = m_world->CreateBody(&ballbd);
	      sbody->CreateFixture(&ballfd);
	    }
    }


    //!##The pulley system with basket and platform
    /*!
     * ###b2BodyDef *bd;
     * bd is body definition and its type is set as dyamic bodywith position as -30,10
     * ###b2PolygonShape bs1;
     * bs1 is a polygon defined here.
     * ###b2FixtureDef *fd1 
     * it contains the properties for body bs1, like density = 10, friction = 5, restitution =0.
     * 
     * Similarly it is done for bs2, fd2, bs3, fd3. These all represents the three walls of the box.
     * ###b2Body* box1;
     * This refers to the box hanging on the left side of pulley and by setting its fixture, all three walls are assigned to it.
     * Then for the horizontal bar hanging on the right seide of pulley, position of bd is modified and density is changed to 44 so that it only starts lifting when the box contain atleast 2 balls.
     * ###b2PulleyJointDef* myjoint;
     * This joint will ensure the proper functioning of pulley. It has been initialized to proper positions.
     * 
     * As the two balls fall in the bucket, it starts lowering and the platform on other side starts lifting and then they have corresponding consequences.
     */
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(-30,10);
      bd->fixedRotation = true;
    

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

      bd->position.Set(-20,10);	
      fd1->density = 44.0;	  //changes to 44
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);


      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(0,0); 
      b2Vec2 worldAnchorOnBody2(0, 0); 
      b2Vec2 worldAnchorGround1(-30, 15);
      b2Vec2 worldAnchorGround2(-20, 15);
      float32 ratio = 1.0f;
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }


    //rotating platform 1 with ball which is hit by pullry on right 
    //! Rotating platform with a ball kept on it
    /*!###b2PolygonShape shape
     * It is a polygon shape object whose dimensions are set as 2.2,0.2
     *  ###b2BodyDef bd;
     * bd is body definition and its type is set as dyamic bodywith position as -17,12
     * ###b2FixtureDef *fd 
     * it contains the properties for body , like density = 1 and its shape is set as defined by variable shape.
     * ###b2Body* body
     * body refers to the horizontal bar.
     * b2PolygonShape shape2
     * It is a polygon shape object whose dimensions are set as 0.2,0.2
     *  ###b2BodyDef bd2;
     * bd2 is body definition with position as -17,12
     * ###b2Body* body2
     * body2 refers to the body for hinging.
     * ###b2RevoluteJointDef jointDef
     * revolute joint used for defining the hinge for the rotating bar.
     * 
     * 
     *  ###b2CircleShape circle;
          "circle" is a circular object of radius 1m. This is the size of a sphere present on the platform.
        ###b2FixtureDef ballfd;
          "ballfd" is a fixture definition whose shape is set by the above defined variable "circle" i.e of a circle, 
          density is set as 5 Kg/m^2, friction and restitution coefficient are set as 0.0. 
        ###b2BodyDef ballbd;
          "ballbd" is body definition -17,12.5, 
          where "i" varies from 0 to 4. In each iteration a new circular object (sphere) is made. "ballbd" is a dynamic type object.  
        ###b2Body* sbody;
          "sbody" is a pointer to rigid body object which is a sphere.
        
     * */
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(-17.0f, 12.0f);
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
      bd2.position.Set(-17.0f, 12.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);

      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
			
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 5.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(-17.0, 12.5f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }


    // rotating platform 2 pulley 2 platform 4 ball
    {
      b2PolygonShape shape;
      shape.SetAsBox(4.0f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(-11.0f, 10.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.0f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(-11.0f, 10.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);


      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);




      b2PolygonShape shape1;
      shape1.SetAsBox(4.0f, 0.2f);
	
      b2BodyDef bd1;
      bd1.position.Set(-10.0f, 16.0f);
      bd1.type = b2_dynamicBody;
      b2Body* body1 = m_world->CreateBody(&bd1);
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 1.0f;
      fd1->shape = new b2PolygonShape;
      fd1->shape = &shape1;
      body1->CreateFixture(fd1);

      b2PolygonShape shape3;
      shape3.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd3;
      bd3.position.Set(-10.0f, 16.0f);
      b2Body* body3 = m_world->CreateBody(&bd3);


      b2RevoluteJointDef jointDef1;
      jointDef1.bodyA = body1;
      jointDef1.bodyB = body3;
      jointDef1.localAnchorA.Set(0,0);
      jointDef1.localAnchorB.Set(0,0);
      jointDef1.collideConnected = false;
      jointDef.upperAngle = 180*(3.14/180);
      jointDef.enableLimit = true;
      m_world->CreateJoint(&jointDef1);



      b2PolygonShape shape4;
      shape4.SetAsBox(0.5f, 0.5f);
      
      b2BodyDef bd4;
      bd4.position.Set(-11.0f, 15.29);
      b2Body* body4 = m_world->CreateBody(&bd4);
      b2FixtureDef *fd4 = new b2FixtureDef;
      fd4->density = 1.0f;
      fd4->shape = new b2PolygonShape;
      fd4->shape = &shape4;
      body4->CreateFixture(fd4);


      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
			
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 5.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(-11, 16.5f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);




      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(-7,10); 
      b2Vec2 worldAnchorOnBody2(-9, 16); 
      b2Vec2 worldAnchorGround1(-7, 20);
      b2Vec2 worldAnchorGround2(-9, 20);
      float32 ratio = 1.0f;
      myjoint->Initialize(body, body1, worldAnchorGround1, worldAnchorGround2, worldAnchorOnBody1, worldAnchorOnBody2, ratio);
      m_world->CreateJoint(myjoint);
    }


    //hammer, platform , tilted platform, curved tunnel
    //!horizontal platform under hammer
/*!
###b2PolygonShape shape
This is a shape variable whose size is set as 8x2.
###b2BodyDef bd
This body definition is for the horizontal bar placed under the hammer. its position is set as 0,8.
###b2Body* body
This variable refers to the above mentioned horizontal bar.
* ###b2FixtureDef *fd 
* fd is the fixture definition variable which contains the detail about the properties of the horizontal platform. Here density is set as 1 and 
* shape is set as defined by shape variable.
* */
//!hammer
/*!
###b2PolygonShape shape1;
* shape1 is the polygon shape object which is a rectangle of size 0.2x4. This is the handle of hammer
* ###b2BodyDef bd1;
* bd1 is the body definition for the handle of hammer, which is of type dynamic and whose position is set as 0,13.
* ###b2Body* body1
* body1 is the b2Body variable which refers to the handle of the hammer
* ###b2FixtureDef *fd1
* fd1 is the fixture definition which contains the properties of the handle of the hammer, like density=1 and shape is set as defined by shape1 variable.
* ###b2PolygonShape shape2;
* shape2 is the polygon shape object which is a rectangle of size 2x1. This is the top of hammer
* ###b2FixtureDef *fd2
* fd2 is the fixture definition which contains the properties of the top of the hammer, like density=1000 and shape is set as defined by shape2 variable.
* 
* Here density is kept very hign so that upper part of hammer causes the hammer to rotate very fast and give a good momentum to the ball.
* ###b2PolygonShape shape3;
* shape3 is the polygon shape object which is a rectangle of size 2x0.2. This will be used for the purpose of hinging.
* ###b2RevoluteJointDef jointDef;
* This variable is the joint definition for the hinges of the rotating platform. Local anchors are located at the centre of each object. 

*/

    {

      b2PolygonShape shape;
      shape.SetAsBox(8.0f, 0.2f);
      
      b2BodyDef bd;
      bd.position.Set(0.0f, 8.0f);
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.0f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);



      b2PolygonShape shape1;
      shape1.SetAsBox(0.2f, 4.0f);
      
      b2BodyDef bd1;
      bd1.position.Set(0.0f, 13.0f);
      bd1.type = b2_dynamicBody;
      b2Body* body1 = m_world->CreateBody(&bd1);
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 1.0f;
      fd1->shape = new b2PolygonShape;
      fd1->shape = &shape1;

      b2PolygonShape shape2;
      shape2.SetAsBox(2.0f, 1.0f, b2Vec2(0.0f,3.1f), 0);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1000.0f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape2;

      body1->CreateFixture(fd1);
      body1->CreateFixture(fd2);


      b2PolygonShape shape3;
      shape3.SetAsBox(2.0f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(0.0f, 13.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);


      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body1;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
//! tilted platorm
/*!
 * ###b2PolygonShape shape5;
* shape5 is the polygon shape object which is a rectangle of size 4x0.25. This is the tilted platform, so that when ball comes rolling on it then it rises and enters in tunnel.
* ### b2BodyDef bd5;
* bd5 is the body definition for the above mentioned bar. Its position is set as 7,10 and angle is set by 0.5
* ###b2Body* body5
 * body5 is the b2Body variable which refers to this tilted platform.
 * Then fixtures are set for this body5 with density being 0 and shape being defined by shape5 variable.
 * */
      b2PolygonShape shape5;
      shape5.SetAsBox(4.0f, 0.25f, b2Vec2(0.f,0.f), 0.5f);
  

      b2BodyDef bd5;
      bd5.position.Set(7.0f, 10.0f);
      b2Body* body5 = m_world->CreateBody(&bd5);
      body5->CreateFixture(&shape5, 0.0f);

//!Curved tunnel
/*!
 * Tunnel is made using the parametric equation of the curve where centre is set as 13,8 and radius bein 8. init=-0.4, is the initial value of the cos0 where theta is the parameter of equation
 * ###b2Body* b1; 
 * bd1 is the b2Body variable which refers to a edge using which a circle will be made.
 * ###b2EdgeShape shape
 * This is the edge shape object.
 * ###float x, y
 * These variables are the x and y coordinates from where the lines will be drawn. These are calculate using the parametric equatoin of circle.
 * ###float tempx,tempy
 * These variables denotes the next position of the parametric x and y. and an edge is drawn b/w x,y and tempx , tempy.
 * This is carried out in loop thus generating many edges to make it look like a circle.
 * */
      {
        float x0 = 13.0f, y0 = 8.0, r= 8,init=-0.40;

        b2Body* b1; 
        b2EdgeShape shape; 
        b2BodyDef bd;
        b1 = m_world->CreateBody(&bd);
        float x=x0 + r*init;
        float y=y0 + r * sqrt(1 - init*init);
        for(float i=init; i <=1.0; i+=0.05){
          float tempx = x0 + r * i;
          float tempy = y0 + r * sqrt(1 - i*i);
          shape.Set(b2Vec2(tempx,tempy), b2Vec2(x, y));
          b1->CreateFixture(&shape, 0.0f); 
          x=tempx;
          y=tempy;
        }
/*! The above mentioned same procedure repeats again, but now with radius equal to 3 so that a inner circle is drawn
 * Then init is modified and again circles are drawn both inner and outer.
 * 
 * */
        r = 3.0;

        x=x0 + r*init;
        y=y0 + r * sqrt(1 - init*init);


        for(float i=init; i <=1.0; i+=0.05){
          float tempx = x0 + r * i;
          float tempy = y0 + r * sqrt(1 - i*i);
          shape.Set(b2Vec2(tempx,tempy), b2Vec2(x, y));
          b1->CreateFixture(&shape, 0.0f); 
          x=tempx;
          y=tempy;
        }

        init = -1.0;
        x=x0 - r*init;
        y=y0 - r * sqrt(1 - init*init);
        for(float i=init; i <-0.6; i+=0.05){
          float tempx = x0 - r * i;
          float tempy = y0 - r * sqrt(1 - i*i);
          shape.Set(b2Vec2(tempx,tempy), b2Vec2(x, y));
          b1->CreateFixture(&shape, 0.0f); 
          x=tempx;
          y=tempy;
        }

        r=8;
        init = -1.0;
        x=x0 - r*init;
        y=y0 - r * sqrt(1 - init*init);
        for(float i=init; i <-0.65; i+=0.05){
          float tempx = x0 - r * i;
          float tempy = y0 - r * sqrt(1 - i*i);
          shape.Set(b2Vec2(tempx,tempy), b2Vec2(x, y));
          b1->CreateFixture(&shape, 0.0f); 
          x=tempx;
          y=tempy;
        }
      }
    }


     //rotating machine pt1 which is hit by pulley 1basket
    {
      float a[] = {-34.0,-37.0,-40.0};
      float b[] = {5.0,6.5,5.0};
      
      for(int i=0;i<3;i++){ 
        b2PolygonShape shape1;
        shape1.SetAsBox(2.0f, 0.2f);
        
        b2BodyDef bd;
        bd.position.Set(a[i], b[i]);
        bd.type = b2_dynamicBody;
        b2Body* body = m_world->CreateBody(&bd);
        b2FixtureDef *fd = new b2FixtureDef;
        fd->density = 1.0f;
        fd->shape = new b2PolygonShape;
        fd->shape = &shape1;
        body->CreateFixture(fd);

        b2PolygonShape shape2;
        shape2.SetAsBox(0.2f, 2.0f);
        b2BodyDef bd2;
        bd2.position.Set(a[i],b[i]);
        b2Body* body2 = m_world->CreateBody(&bd2);


        b2RevoluteJointDef jointDef;
        jointDef.bodyA = body;
        jointDef.bodyB = body2;
        jointDef.localAnchorA.Set(0,0);
        jointDef.localAnchorB.Set(0,0);
        jointDef.collideConnected = false;
        m_world->CreateJoint(&jointDef);
      }

    }
//!L-shaped bucket hanging at the left end of the simulation.
    //bucket pendulum which contains ball 
    {
/*!
 *  ###b2BodyDef *bd;
     * bd is body definition and its type is set as dyamic bodywith position as -43.5,8. This refers to the vertical bar present in that L.
     * ###b2PolygonShape bs1;
     * bs1 is a polygon defined here whose size is 2x0.2
     * ###b2FixtureDef *fd1 
     * it contains the properties for body bs1, like density = 0, friction = 0.5, restitution =0.Its shape is also set as defined by variable bs1.
     * 
 *   * ###b2PolygonShape bs2;
     * bs1 is a polygon defined here whose size is 0.2x2.
     * ###b2FixtureDef *fd2
     * it contains the properties for body bs2, like density = 0, friction = 0.5, restitution =0.Its shape is also set as defined by variable bs2.
     * And this body refers to the horizontal bar of that L
     * ### b2Body* box1
     * Box1 is b2body type variable which refers to the L shaped object.fd1 and fd2 are attached to this bar.
 * 
 * ### b2Body* b2;
 * ###b2PolygonShape bs1;
     * bs1 is a polygon defined here whose size is 0.25x0.25.This body refers to another body which is required to hinge this
     * ###BodyDef *bd;
     * bd is body definition and its position as -43.5,36. 
     * ###b2RevoluteJointDef jd
     * jd is the revolute joint to create hinge between the L and the vertically hanging rope.
 * 
 * 
 * */
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(-43.5,8);
    

      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 0.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
      fd1->shape = &bs1;

    
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 0.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(-2.0f,0.f), 0);
      fd2->shape = &bs2;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);

      b2Body* b2;
      {
        b2PolygonShape shape;
        shape.SetAsBox(0.25f, 0.25f);
          
        b2BodyDef bd;
        bd.position.Set(-43.5f, 36.0f);
        b2 = m_world->CreateBody(&bd);
        b2->CreateFixture(&shape, 10.0f);
      }
  
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-43.5f, 40.0f);
      jd.Initialize(b2, box1, anchor);
      m_world->CreateJoint(&jd);
    }
    
    //!curves at the middle of the design with a hole using parametric equation
    /*!
     *  Curve is made using the parametric equation of the curve where centre is set as -30,15 and radius being 20. init=-0.4, is the initial value of the cos0 where theta is the parameter of equation
 * ###b2Body* b1; 
 * bd1 is the b2Body variable which refers to a edge using which a circle will be made.
 * ###b2EdgeShape shape
 * This is the edge shape object.
 * ###float x, y
 * These variables are the x and y coordinates from where the lines will be drawn. These are calculate using the parametric equatoin of circle.
 * ###float tempx,tempy
 * These variables denotes the next position of the parametric x and y. and an edge is drawn b/w x,y and tempx , tempy.
 
     * */
    {
      float x0 = -30.0f, y0 = 15.0, r= 20,init=-0.40;

      b2Body* b1; 
      b2EdgeShape shape; 
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      float x=x0 - r*init;
      float y=y0 - r * sqrt(1 - init*init);
      for(float i=init; i <1.0; i+=0.05){
        float tempx = x0 - r * i;
        float tempy = y0 - r * sqrt(1 - i*i);
        shape.Set(b2Vec2(tempx,tempy), b2Vec2(x, y));
        b1->CreateFixture(&shape, 0.0f); 
        x=tempx;
        y=tempy;
      }
      shape.Set(b2Vec2(-50.0,50), b2Vec2(x, y));
      b1->CreateFixture(&shape, 0.0f);
/*! Then again two more curves are made using the same logic as above*/
      x0 = -5.0;
      y0 = 20.0;
      r = 30.0;
      init = -0.80;
      x=x0 - r*init;
      y=y0 - r * sqrt(1 - init*init);

      // shape.Set(b2Vec2(18,50), b2Vec2(x, y));
      // b1->CreateFixture(&shape, 0.0f);

      for(float i=init; i <-0.05; i+=0.05){
        float tempx = x0 - r * i;
        float tempy = y0 - r * sqrt(1 - i*i);
        shape.Set(b2Vec2(tempx,tempy), b2Vec2(x, y));
        b1->CreateFixture(&shape, 0.0f); 
        x=tempx;
        y=tempy;
      }
      init = 0.05;
      x=x0 - r*init;
      y=y0 - r * sqrt(1 - init*init);
      for(float i=init; i <0.6; i+=0.05){
        float tempx = x0 - r * i;
        float tempy = y0 - r * sqrt(1 - i*i);
        shape.Set(b2Vec2(tempx,tempy), b2Vec2(x, y));
        b1->CreateFixture(&shape, 0.0f); 
        x=tempx;
        y=tempy;
      }

    }

    //!rotating platform with shelves for balls which then hits dominos
    /*!
     * In this three platforms are made, and a series of dominos is kept on each one of them. Adjacent to each platform a rotating bar with a 
     * ball on it is kept. when ball hits the bar, these balls hit the dominos and results in their falling.
     * */
    
    {
      b2PolygonShape shape;
      shape.SetAsBox(8.0f, 0.2f);
  
      b2BodyDef bd;
      bd.position.Set(-8.0f, -35.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.0f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      shape.SetAsBox(0.2f,10.0f,b2Vec2(-8.0,9.0),0);
      body->CreateFixture(fd);

      for (int i=0;i<3;i++){ //change to 3
        shape.SetAsBox(3.0f,0.2f,b2Vec2(-11.0f,2.1+i*6.0f),0.2);
        body->CreateFixture(fd);
      }

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(-8.0f, -35.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);


      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      //jointDef.lowerAngle = 180*(3.14/180);
      jointDef.upperAngle = 5*(3.14/180);
      jointDef.enableLimit = true;
      m_world->CreateJoint(&jointDef);


      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
      
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      
      for(int i=0;i<3;i++){
        ballbd.position.Set(-17.0, -32.0f + i*6.0f);
        sbody = m_world->CreateBody(&ballbd);
        sbody->CreateFixture(&ballfd);
      }

      {
        b2PolygonShape shape;
        shape.SetAsBox(10.0f, 0.2f);
        b2FixtureDef *fd = new b2FixtureDef;
        fd->density = 1.0f;
        fd->shape = new b2PolygonShape;
        fd->shape = &shape;
        b2BodyDef bd;
        for(int i=0;i<3;i++){
          bd.position.Set(-32.5f, -33.0f + i*6.0f);
          b2Body* body = m_world->CreateBody(&bd);
          body->CreateFixture(fd);
        }
      }

      {
        b2PolygonShape shape;
        shape.SetAsBox(0.2f, 2.0f);
        b2FixtureDef *fd = new b2FixtureDef;
        fd->density = 0.5f;
        fd->shape = new b2PolygonShape;
        fd->shape = &shape;
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        for(int i=0;i<3;i++){
          for(int j=0;j<10;j++){
            bd.position.Set(-23.5f - j*2.0f, -28.5f + i*6.0f);
            b2Body* body = m_world->CreateBody(&bd);
            body->CreateFixture(fd);
          }
        }
      }

    }


    //curve below domino system with  a gap to contain two balls + a rotatin platform +   boundary of whole simulation + water platform for bot at the end
    //
    /*!##Curve below domino system and Boundary of simulation
      ###b2Body* b1
      This is the body object which acts as curved surface which holds three balls and also defines the boundary of the simulation.
      ###b2EdgeShape shape
      This defines the edge shape object which varies according to need sometime as a circular shape according to parametric equation and sometime as  boundary of the simulation.
      ###b2BodyDef bd;
      This defines the body defintion object for hre edge shape whic defines positon of the shape.

      This actsas the boundary of the simulation and also it partions the simulation from center part and down part. This acts as pocket for three balls which are hold in the hole on the edge shape.
    */
    {
      float x0 = -30.0f, y0 = 15.0, r= 20,init=-0.40;

      b2Body* b1; 
      b2EdgeShape shape; 
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      float x=x0 - r*init;
      float y=y0 - r * sqrt(1 - init*init);


      x0 = -5.0;
      y0 = -10.0;
      r = 30.0;
      init = -0.80;
      x=x0 - r*init;
      y=y0 - r * sqrt(1 - init*init);


      for(float i=init; i <-0.05; i+=0.05){
        float tempx = x0 - r * i;
        float tempy = y0 - r * sqrt(1 - i*i);
        shape.Set(b2Vec2(tempx,tempy), b2Vec2(x, y));
        b1->CreateFixture(&shape, 0.0f); 
        x=tempx;
        y=tempy;
      }

      shape.Set(b2Vec2(x,y-2), b2Vec2(x, y));
      b1->CreateFixture(&shape, 0.0f);
      shape.Set(b2Vec2(x,y-2), b2Vec2(x-4, y-2));
      b1->CreateFixture(&shape, 0.0f);
      shape.Set(b2Vec2(x-4,y), b2Vec2(x-4, y-2));
      b1->CreateFixture(&shape, 0.0f);


      x=x-4;
      y=y;




      shape.Set(b2Vec2(x,y), b2Vec2(x-30, y-1.5f));
      b1->CreateFixture(&shape, 0.0f);


      //boundary

      shape.Set(b2Vec2(x-50,50), b2Vec2(x-50, -85)); //change to -85 maybe
      b1->CreateFixture(&shape, 0.0f); 
      shape.Set(b2Vec2(86,-85), b2Vec2(x-50, -85));
      b1->CreateFixture(&shape, 0.0f);
      shape.Set(b2Vec2(90,-85), b2Vec2(100, -85));
      b1->CreateFixture(&shape, 0.0f);
      shape.Set(b2Vec2(100,-85), b2Vec2(100, 50));
      b1->CreateFixture(&shape, 0.0f);
      shape.Set(b2Vec2(x-50,50), b2Vec2(100, 50));
      b1->CreateFixture(&shape, 0.0f);


      /*!## Rotating Platform which slides ball towards pendulum group
        ###b2PolygonShape shape 
        This defines shape of object which consist of Box shaped object of size 24 x 0.4..
        ###b2BodyDef bd 
        Body definition of object platform at postion (x-35.y-4)) and body type dynamic.
        ###b2Body* body 
        body defines body which keep changing shape to make a platform object which tilts by falling of domino and which then gives direction to ball to hit pendulum sysytem.
        ###b2FixtureDef *fd 
        This is fixture definition of platform with density 1 and shape as abpve.
        ###b2PolygonShape shape2 
        This is the rectangular shaped object of width 4.0 and length 0.4.
        ###b2BodyDef bd2 
        Body definition of object whch sets postion at x-355, y-4 and make it static body.
        ###b2Body* body2 
        This defines the body representing hidden box which acts as hinge for the fructum.
        ###b2RevoluteJointDef jointDef 
        Joint Definition which joins body and body2 to make a rotating platform.

        This is the object made to direct falling domino towards the ball which then rolls over it towards the pendulum group.
       */ 
      {
        b2PolygonShape shape1;
        shape1.SetAsBox(12.0f, 0.2f);
        
        b2BodyDef bd;
        bd.position.Set(x-35, y-4);
        bd.type = b2_dynamicBody;
        b2Body* body = m_world->CreateBody(&bd);
        b2FixtureDef *fd = new b2FixtureDef;
        fd->density = 1.0f;
        fd->shape = new b2PolygonShape;
        fd->shape = &shape1;
        body->CreateFixture(fd);

        b2PolygonShape shape2;
        shape2.SetAsBox(0.2f, 2.0f);
        b2BodyDef bd2;
        bd2.position.Set(x-35,y-4);
        b2Body* body2 = m_world->CreateBody(&bd2);


        b2RevoluteJointDef jointDef;
        jointDef.bodyA = body;
        jointDef.bodyB = body2;
        jointDef.localAnchorA.Set(0,0);
        jointDef.localAnchorB.Set(0,0);
        jointDef.collideConnected = false;
        m_world->CreateJoint(&jointDef);
      }


     /*!Platform on which boat moves
        ###b2PolygonShape shape
        This is a rectangular shaped object of size 150-x/2 * 0.4.
        ###b2FixtureDef *fd 
        This defines the fixture of platform as density 1 and friction as 0.0 so boat can slide on it.
        ###b2BodyDef bd;
        Body definiton of the object to place it at 50+x/2, -95
        ###b2Body* body
        Body object which is used as Sea object for the boat to move on it frictionlessly.
     */

      {
        b2PolygonShape shape;
        shape.SetAsBox((150-x)/2, 0.2f);
        b2FixtureDef *fd = new b2FixtureDef;
        fd->density = 1.0f;
        fd->friction = 0.0f;
        fd->shape = new b2PolygonShape;
        fd->shape = &shape;
        b2BodyDef bd;
        bd.position.Set((50+x)/2, -95.0f );
        b2Body* body = m_world->CreateBody(&bd);
        body->CreateFixture(fd);
      }
    }

    //pendulum group of 6 pendulum + dominos with 10 domino
    /*!## Pendulum group 
        ###b2CircleShape circle; 
        "circle" is a circular object of radius 1m. 
        ###b2FixtureDef ballfd; 
        "ballfd" is a fixture definition whose shape is set by the above defined variable "circle" i.e of a circle, density is set as 2 Kg/m^2, friction and restitution coefficient are set as 0.0. 
        ###b2BodyDef ballbd; 
        "ballbd" is body definition and its position is set by for loop to make 6 different pendulum bob's.
        ###b2Body* sBody; 
        This is the body defining pendulum objects to make a series of pendulum which hit each other and finally hits domino to initialise their motion. 
        ###b2Body* b2;   
        This is the body which acts as hinge object fot the pendulum object.
        ###b2PolygonShape shape1;
        Shape of the hinge object is set as 0,5 x 0.5 and placed acording to for loop to make 6 hinges.

        This is the pendulum series which at the end hits dominos objects which then hits the small ball.
     */
    {

      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
      
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 2.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;

      

      b2Body* b2;
    
      b2PolygonShape shape1;
      shape1.SetAsBox(0.25f, 0.25f);
    
  
      b2RevoluteJointDef jd;
      b2Vec2 anchor;

      for(int i=0;i<6;i++){
        ballbd.position.Set(-53.5f+i*2.0, -55.0f);
        sbody = m_world->CreateBody(&ballbd);
        sbody->CreateFixture(&ballfd);
        anchor.Set(-53.5f+i*2.0f, -46.0f);

        b2BodyDef bd;
        bd.position.Set(-53.5f+i*2.0f, -46.0f);
        b2 = m_world->CreateBody(&bd);
        b2->CreateFixture(&shape1, 10.0f);
        jd.Initialize(b2, sbody, anchor);
        m_world->CreateJoint(&jd);
      }
      /*!##Domino System
        ###b2Body* b1; 
        Body reprsenting platform on which dominos are placed.
        ###b2EdgeShape shape; 
        This is the edge shape object joining -41,-58 to -22,-58.
        ###b2BodyDef bd;
        This defines the body definition of edge object to make platform for dominos.
        ###b2PolygonShape shape; 
        This is the domino object's shape of size 0.4 x 4.0. 
        ###b2FixtureDef *fd;
        This is the fixture definiton of object with denisty 5 and shape as defined above.
        ###b2BodyDef bd;
        This is body definition which keeps changing position to make 10 different domino object.

        This platform and domino series is made to to hit the small ball kept at the platform below it which after it hits mass to make pulley move.
      */
      {
        b2Body* b1; 
        b2EdgeShape shape; 
        b2BodyDef bd;
        b1 = m_world->CreateBody(&bd);
        shape.Set(b2Vec2(-41.0,-58), b2Vec2(-22.0, -58));
        b1->CreateFixture(&shape, 0.0f);
      }
      {
        b2PolygonShape shape;
        shape.SetAsBox(0.2f, 2.0f);
        b2FixtureDef *fd = new b2FixtureDef;
        fd->density = 5.0f;
        fd->shape = new b2PolygonShape;
        fd->shape = &shape;
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        for(int j=0;j<10;j++){
          bd.position.Set(-41.0f + j*2.0f, -56.0f);
          b2Body* body = m_world->CreateBody(&bd);
          body->CreateFixture(fd);
        }
      }
    }

    //platform below domnios + ball platform which hits heavy mass with pulley to shoot the ball 
    /*!## Rotating Platform which slides Domino
        ###b2PolygonShape shape 
        This defines shape of object which consist of Box shaped object of size 16 x 0.4..
        ###b2BodyDef bd 
        Body definition of object platform at postion (-25.5,65)) and body type dynamic.
        ###b2Body* body 
        body defines body which keep changing shape to make a platfomr object which tilts by falling of domino and which then hits the ball.
        ###b2FixtureDef *fd 
        This is fixture definition of platform with density 1 and shape as abpve.
        ###b2PolygonShape shape2 
        This is the rectangular shaped object of width 4.0 and length 0.4.
        ###b2BodyDef bd2 
        Body definition of object whch sets postion at -25.5, -65 and make it static body.
        ###b2Body* body2 
        This defines the body representing hidden box which acts as hinge for the fructum.
        ###b2RevoluteJointDef jointDef 
        Joint Definition which joins body and body2 to make a rotating platform.

        This is the object made to direct falling domino towards the ball which then hits mass object to pull pulley string.
       */ 
    {
      b2PolygonShape shape;
      shape.SetAsBox(8.0f, 0.2f);
  
      b2BodyDef bd;
      bd.position.Set(-25.5f, -65.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.0f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(-25.5f, -65.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);


      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      //jointDef.lowerAngle = 180*(3.14/180);
      jointDef.upperAngle = 20*(3.14/180);
      jointDef.enableLimit = true;
      m_world->CreateJoint(&jointDef);


      /*!##Ball
        ###b2CircleShape circle; 
        "circle" is a circular object of radius 1m. 
        ###b2FixtureDef ballfd; 
        "ballfd" is a fixture definition whose shape is set by the above defined variable "circle" i.e of a circle, density is set as 50 Kg/m^2, friction and restitution coefficient are set as 0.0. 
        ###b2BodyDef ballbd; 
        "ballbd" is body definition and its position is set to (-15,-65)
        ###b2Body* sBody; 
        "sBody" is a pointer to rigid body object which is a sphere.

        This body acts as the ball which hits Big Balls after jumping from pulley mechanism when strings are pulled from mass.
      */
      
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
      ballbd.position.Set(-15, -65.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);

      /*!##Slant edge and small ball
        ###b2Body* b1; 
        Body to represent slant edge on which small ball and mass is placed.
        ###b2EdgeShape shape
         Shape object to make the slant platform. -17.0,-70 to 17, -76
        ###b2BodyDef bd 
        Body definition of edge object.

        ###b2CircleShape circle; 
        "circle" is a circular object of radius 0.8m. 
        ###b2FixtureDef ballfd; 
        "ballfd" is a fixture definition whose shape is set by the above defined variable "circle" i.e of a circle, density is set as 10 Kg/m^2, friction and restitution coefficient are set as 0.0. 
        ###b2BodyDef ballbd; 
        "ballbd" is body definition and its position is set to (-15,-69)
        ###b2Body* sBody; 
        "sBody" is a pointer to rigid body object which is a sphere ball.

        This platform is to place the small ball and mass which is attached to the pulley.
       */

      {
        b2Body* b1; 
        b2EdgeShape shape; 
        b2BodyDef bd;
        b1 = m_world->CreateBody(&bd);
        shape.Set(b2Vec2(-17.0,-70), b2Vec2(-14.5, -70));
        b1->CreateFixture(&shape, 0.0f);
        shape.Set(b2Vec2(-14.5,-70), b2Vec2(17.0, -76)); //change to -75 -> -76
        b1->CreateFixture(&shape, 0.0f);
        // shape.Set(b2Vec2(-18.5,-68), b2Vec2(-18.5, -66));
        // b1->CreateFixture(&shape, 0.0f);
        
        b2Body* sbody;
        b2CircleShape circle;
        circle.m_radius = 0.8;
        b2FixtureDef ballfd;
        ballfd.shape = &circle;
        ballfd.density = 10.0f;
        ballfd.friction = 0.0f;
        ballfd.restitution = 0.0f;
        b2BodyDef ballbd;
        ballbd.type = b2_dynamicBody;
        ballbd.position.Set(-15.0, -69.0f);
        sbody = m_world->CreateBody(&ballbd);
        sbody->CreateFixture(&ballfd);
      }

      /*!##Pulley with one end at rotating platform and one end at mass
        ###b2PolygonShape shape 
        This defines shape of object which consist of a rotating platform.
        ###b2BodyDef bd 
        Body definition of object platform at postion (-10,-67) and body type dynamic.
        ###b2Body* body 
        body defines body which keep changing shape to make a platform object. This acts as hitting bat for ball to move into tunnel.
        ###b2FixtureDef *fd 
        This is fixture definition of fructum with density 1 and shape mentioned above.
        ###b2PolygonShape shape2 
        This is the rectangular shaped object of width 4.0 and length 0.4.
        ###b2BodyDef bd2 Body 
        definition of object whch sets postion at -3,-67 and make it static body.
        ###b2Body* body2 
        This defines the body representing hidden box which acts as hinge for the fructum.
        ###b2RevoluteJointDef jointDef 
        Joint Definition which joins body and body2 to make a rotatable fructum to hit ball.

        ###b2PolygonShape shape1 
        This is square shape object with 2x2 size.
        ###b2BodyDef bd1 
        body definition at postion 16.7,-75 and a dynamic body.
        ###b2Body* body1 
        This defines mass object which pulls pulley's one end to pull one end of platform to make ball fly towards tunnel.
        ###b2FixtureDef *fd1  
        this is fixture definition of mass with density 500 to pull platform.
        ###b2PulleyJointDef* myjoint 
        this is the pulley object which acts as mechanism for flying the ball towards tunnel.

          This defines mass object which pulls pulley's one end to pull one end of platform to make ball fly towards tunnel.
       */
      {
        b2PolygonShape shape;
        shape.SetAsBox(7.0f, 0.2f);
    
        b2BodyDef bd;
        bd.position.Set(-10.0f, -67.0f);
        bd.type = b2_dynamicBody;
        b2Body* body = m_world->CreateBody(&bd);
        b2FixtureDef *fd = new b2FixtureDef;
        fd->density = 1.0f;
        fd->shape = new b2PolygonShape;
        fd->shape = &shape;
        body->CreateFixture(fd);

        b2PolygonShape shape2;
        shape2.SetAsBox(0.2f, 2.0f);
        b2BodyDef bd2;
        bd2.position.Set(-3.0f, -67.0f);
        b2Body* body2 = m_world->CreateBody(&bd2);


        b2RevoluteJointDef jointDef;
        jointDef.bodyA = body;
        jointDef.bodyB = body2;
        jointDef.localAnchorA.Set(7.0,0);
        jointDef.localAnchorB.Set(0,0);
        jointDef.collideConnected = false;
        m_world->CreateJoint(&jointDef);




        b2PolygonShape shape1;
        shape1.SetAsBox(1.0f, 1.0f);
    
        b2BodyDef bd1;
        bd1.position.Set(16.7f, -75);
        bd1.type = b2_dynamicBody;
        b2Body* body1 = m_world->CreateBody(&bd1);
        b2FixtureDef *fd1 = new b2FixtureDef;
        fd1->density = 500.0f;
        fd1->shape = new b2PolygonShape;
        fd1->shape = &shape1;
        body1->CreateFixture(fd1);

        




        b2PulleyJointDef* myjoint = new b2PulleyJointDef();
        b2Vec2 worldAnchorOnBody1(-17.0,-67.0); 
        b2Vec2 worldAnchorOnBody2(16.7, -75); 
        b2Vec2 worldAnchorGround1(-17.0,-55);
        b2Vec2 worldAnchorGround2(16.7f, -55);
        float32 ratio = 1.0f;
        myjoint->Initialize(body, body1, worldAnchorGround1, worldAnchorGround2, worldAnchorOnBody1, worldAnchorOnBody2, ratio);
        m_world->CreateJoint(myjoint);
      }

    }

    /*!##Tunnel through which ball goes to hit Big balls
      ###Body* body 
      which is used to make tunnel through which ball moves after thrown from platform.
      ###b2EdgeShape shape 
      Edge shape body which changes as needed to make two circular arcs to make tunnel like shape. Circular Shape is made using parametric equation of circle. First circle is of radius 15 and other of 20. Both with center (5,-62).
      
      
      This object is used to direct ball towards big balls so that it can hit them and move them forward towards motor.
    */
    //tunnel through which ball goes to hit big balls + big balls + motor to hit balls
    {
      float x0 = 5.0f, y0 = -62.0, r= 15,init=-0.40;

      b2Body* b1; 
      b2EdgeShape shape; 
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      float x=x0 + r*init;
      float y=y0 + r * sqrt(1 - init*init);
      for(float i=init; i <=1.0; i+=0.05){
        float tempx = x0 + r * i;
        float tempy = y0 + r * sqrt(1 - i*i);
        shape.Set(b2Vec2(tempx,tempy), b2Vec2(x, y));
        b1->CreateFixture(&shape, 0.0f); 
        x=tempx;
        y=tempy;
      }

      shape.Set(b2Vec2(x,y-3), b2Vec2(x, y));
      b1->CreateFixture(&shape, 0.0f); 
      shape.Set(b2Vec2(x,y-3), b2Vec2(x+20, y-3));
      b1->CreateFixture(&shape, 0.0f); 

      r = 20.0;
      x=x0 + r*init;
      y=y0 + r * sqrt(1 - init*init);


      for(float i=init; i <=1.0; i+=0.05){
        float tempx = x0 + r * i;
        float tempy = y0 + r * sqrt(1 - i*i);
        shape.Set(b2Vec2(tempx,tempy), b2Vec2(x, y));
        b1->CreateFixture(&shape, 0.0f); 
        x=tempx;
        y=tempy;
      }
      /*!##Big Balls
        ###b2Body* sbody 
        Body to represent 5 big balls on the horizontal platform which upon hitting motor goes towards fructum.
        ###b2CircleShape circle 
        circle shape object with radius 2 to represent Big balls.
        ###b2FixtureDef ballfd 
        ball's fixture definition with density 2.0 and friction and restitution 0.0.
        ###b2BodyDef ballbd 
        body Definitionwhich sets position at different positions to make 5 different balls.
      
      
          This object is used to make balls which acts as weight for fructum which hits boat to and moves boat.
    */
      {
        b2Body* sbody;
        b2CircleShape circle;
        circle.m_radius = 2;
        b2FixtureDef ballfd;
        ballfd.shape = &circle;
        ballfd.density = 2.0f;
        ballfd.friction = 0.0f;
        ballfd.restitution = 0.0f;
        b2BodyDef ballbd;
        ballbd.type = b2_dynamicBody;
        for(int i=0;i<5;i++){
          ballbd.position.Set(x-1 + i*4, y-2);
          sbody = m_world->CreateBody(&ballbd);
          sbody->CreateFixture(&ballfd);
        }
      }
      
      /*!##Motor
        ###b2PolygonShape 
        shape A box shape to make the bar which represents roatating motor, this is of lenth 20 and width 0.4.
        ###b2BodyDef bd 
        Body definition which sets position at 56,-74 and to make it a dynamic body.
        ###b2Body* body 
        This is body representing motor in the system to place it in world.
        ###b2FixtureDef *fd  
        fixture definition with density 1.0 and shape as the rectangular bar defined above.
        ###b2PolygonShape shape2 
        This is the rectangular shaped object of width 12.0 and length 0.4.
        ###b2BodyDef bd2 
        Body definition of object whch sets postion at 56,-74 and make it static body.
        ###b2Body* body2 
        This defines the body representing hidden box which acts as hinge for the rotating motor.
        ###b2RevoluteJointDef 
        jointDef Joint Definition which joins body and body2 which rotates with Speed 15 and Torque 1000000.0.
        
          This object is used to throw Big balls towards right end of simulation to act as weight for fructum.
    */
      {
				b2PolygonShape shape;
        shape.SetAsBox(10.0f, 0.2f);
    
        b2BodyDef bd;
        bd.position.Set(56.0f, -74.0f);
        bd.type = b2_dynamicBody;
        b2Body* body = m_world->CreateBody(&bd);
        b2FixtureDef *fd = new b2FixtureDef;
        fd->density = 1.0f;
        fd->shape = new b2PolygonShape;
        fd->shape = &shape;
        body->CreateFixture(fd);
        shape.SetAsBox(0.2f,10.0f);
        //body->CreateFixture(fd);

        b2PolygonShape shape2;
        shape2.SetAsBox(0.2f, 6.0f);
        b2BodyDef bd2;
        bd2.position.Set(56.0f, -74.0f);
        b2Body* body2 = m_world->CreateBody(&bd2);


        b2RevoluteJointDef jointDef;
        jointDef.bodyA = body;
        jointDef.bodyB = body2;
        jointDef.localAnchorA.Set(0,0);
        jointDef.localAnchorB.Set(0,0);
        jointDef.collideConnected = false;
        jointDef.enableMotor = true;
        jointDef.motorSpeed =15.0f;
        jointDef.maxMotorTorque = 100000.0f;
        m_world->CreateJoint(&jointDef);    
       }

       /*!## Fructum Object
        ###b2PolygonShape shape 
        This defines shape of object which consist of three parts two horizontal platforms and one vertical platform.
        ###b2BodyDef bd 
        Body definition of object fructum at postion (93.8,-70) and body type dynamic.
        ###b2Body* body 
        body defines body which keep changing shape to make a Z shaped object to replace piston shape to a mechanical object. This acts as hitting bat for bot.
        ###b2FixtureDef *fd 
        This is fixture definition of fructum with density 1 and shape mentioned above.
        ###b2PolygonShape shape2 
        This is the rectangular shaped object of width 12.0 and length 0.4.
        ###b2BodyDef bd2 
        Body definition of object whch sets postion at 56,-74 and make it static body.
        ###b2Body* body2 
        This defines the body representing hidden box which acts as hinge for the fructum.
        ###b2RevoluteJointDef 
        jointDef Joint Definition which joins body and body2 to make a rotatable fructum to hit boat.

          This is the object made to replace piston mehanism as a mechanical object to hit the boat. This activates when big balls fall on one of its horizontal platfotm.
       */
      //system to replace piston a Z

       {
				b2PolygonShape shape;
        shape.SetAsBox(6.0f, 0.2f);
    
        b2BodyDef bd;
        bd.position.Set(93.8f, -70.0f);
        bd.type = b2_dynamicBody;
        b2Body* body = m_world->CreateBody(&bd);
        b2FixtureDef *fd = new b2FixtureDef;
        fd->density = 1.0f;
        fd->shape = new b2PolygonShape;
        fd->shape = &shape;
        body->CreateFixture(fd);
        shape.SetAsBox(0.2f,12.0f,b2Vec2(-6,-12),0);
        body->CreateFixture(fd);
				shape.SetAsBox(2.0f,0.2f,b2Vec2(-8,-24),0);
        body->CreateFixture(fd);


        b2PolygonShape shape2;
        shape2.SetAsBox(0.2f, 6.0f);
        b2BodyDef bd2;
        bd2.position.Set(93.8f, -70.0f);
        b2Body* body2 = m_world->CreateBody(&bd2);


        b2RevoluteJointDef jointDef;
        jointDef.bodyA = body;
        jointDef.bodyB = body2;
        jointDef.localAnchorA.Set(0,0);
        jointDef.localAnchorB.Set(0,0);
        jointDef.upperAngle = 10*(3.14/180);
     		jointDef.enableLimit = true;
        jointDef.collideConnected = false;
        m_world->CreateJoint(&jointDef);    
      }
      {
      	b2Body* b1; 
        b2EdgeShape shape; 
        b2BodyDef bd;
        b1 = m_world->CreateBody(&bd);
        shape.Set(b2Vec2(88.0,-69), b2Vec2(88.0, -64));
        b1->CreateFixture(&shape, 0.0f);
        // shape.Set(b2Vec2(88.0,-69), b2Vec2(88.0, -60));
        // b1->CreateFixture(&shape, 0.0f);
      }
      /*!##Boat
      ###b2PolygonShape shape;
        "shape" is a polygon shape object which is a custom shape object representing Boat which moves when hit from behind. 
        It is made by joining points (-5,1), (2,-2.5), (5,1) and (-2,-2.5) relative to the center placed at (80.0,-90.0) 
      ###b2BodyDef bd;
        bd is body definition and its position is set to (80,90) .
      ###b2FixtureDef fd;
        fd is body fixture definition and its density and friction are set to 0.1 and 0.0 respectively.  
      ###b2Body* body;
        body is a pointer to rigid body object which is the boat object drawn on world.
      

      This object is the boat object which is the final aim of simulation which is moved after a hit from behind by the fulcrum horizontal bar.
    */
      //boat
      {
        b2PolygonShape shape;
        // b2Vec2 vertices[4];
        // vertices[0].Set(-3,2);
        // vertices[1].Set(3,2);
        // vertices[2].Set(2,-2);
        // vertices[3].Set(-2,-2);
        // shape.Set(vertices, 4);
        b2Vec2 vertices[4];
        vertices[1].Set(-5,1);
        vertices[3].Set(2,-2.5);
        vertices[0].Set(5,1);
        vertices[2].Set(-2,-2.5);
        shape.Set(vertices, 4);
        //shape.SetAsBox(3,2);

        b2BodyDef bd;
        bd.position.Set(80.0f, -90.0f);
        bd.type = b2_dynamicBody;
        b2Body* body = m_world->CreateBody(&bd);
        b2FixtureDef *fd = new b2FixtureDef;
        fd->density = 0.1f;
        fd->friction = 0.0f;
        fd->shape = new b2PolygonShape;
        fd->shape = &shape;
        body->CreateFixture(fd);
        
      }

    }











  }
  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
