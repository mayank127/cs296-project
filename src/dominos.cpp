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

      b2PolygonShape shape5;
      shape5.SetAsBox(4.0f, 0.25f, b2Vec2(0.f,0.f), 0.5f);
  

      b2BodyDef bd5;
      bd5.position.Set(7.0f, 10.0f);
      b2Body* body5 = m_world->CreateBody(&bd5);
      body5->CreateFixture(&shape5, 0.0f);


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

    //bucket pendulum which contains ball 
    {

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
    
    //curves at the middle of the design with a hole using parametric equation
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

    //rotating platform with shelves for balls which then hits dominos
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
