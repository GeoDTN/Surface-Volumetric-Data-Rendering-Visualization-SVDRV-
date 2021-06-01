#include "pandaFramework.h"
#include "windowFramework.h"
#include "nodePath.h"
#include "clockObject.h"
#include "asyncTask.h"
#include "genericAsyncTask.h"
#include "bulletWorld.h"
#include "bulletPlaneShape.h"
#include "bulletSphereShape.h"
#include "bulletBoxShape.h"
//define the prototypes
void init_ball1();
void init_ball2();
void init_ball3();
void init_cube();
//define global variables
BulletBoxShape *box_shape;
BulletSphereShape *sphere_shape,*sphere_shape2,*sphere_shape3;
BulletRigidBodyNode
*box_rigid_node,*sphere_rigid_node,*sphere_rigid_node2,*sphere_rigid_node3;
NodePath np_box, np_box_model,np_sphere, np_sphere_model,np_sphere2,
np_sphere_model2,np_sphere3, np_sphere_model3;
PandaFramework framework;
WindowFramework *window;
BulletWorld *physics_world;
// DEFINE INITIAL VELOCITY
LVector3f initialVelBall1 ;
LVector3f initialVelBall2 ;
LVector3f initialVelBall3 ;
ClockObject *co = ClockObject::get_global_clock();
AsyncTaskManager *task_mgr = AsyncTaskManager::get_global_ptr();
AsyncTask::DoneStatus update_scene(GenericAsyncTask* task, void* data)
{
physics_world->do_physics(co->get_dt(), 10, 1.0 / 180.0);
return AsyncTask::DS_cont;
} void reset(const Event *
theEvent, void *
data) //reset function
{
// remove node and rigid body
np_sphere_model2.remove_node();
np_sphere_model.remove_node();
np_sphere_model3.remove_node();
np_box_model.remove_node();
physics_world->remove_rigid_body(sphere_rigid_node);
physics_world->remove_rigid_body(sphere_rigid_node2);
physics_world->remove_rigid_body(sphere_rigid_node3);
physics_world->remove_rigid_body(box_rigid_node);
//initialization of others balls and cube
init_ball1();
init_ball2();
init_ball3();
init_cube();
} void init_cube() // init of the cube
{
box_shape = new BulletBoxShape(*new LVecBase3f(1.0, 1.0, 1.0));
box_rigid_node = new BulletRigidBodyNode("Box");
box_rigid_node->set_mass(1.0); // set mass
box_rigid_node->add_shape(box_shape);
box_rigid_node->set_restitution(1); // set the restitution of the object
physics_world->attach_rigid_body(box_rigid_node);
np_box = window->get_render().attach_new_node(box_rigid_node);
np_box.set_pos_hpr(2, 0, 2, 45, 45, 45);
np_box_model = window->load_model(framework.get_models(), "models/box");
np_box_model.set_pos(-1.0, -1.0, -1.0);
np_box_model.set_scale(2);
np_box_model.reparent_to(np_box);
} void init_ball1() // init ball1
{ initialVelBall1 =(rand()%20-10,rand()%20-10,rand()%20-10); // set randomly the
values ofinitial velocity
sphere_shape = new BulletSphereShape(1.0);
sphere_rigid_node = new BulletRigidBodyNode("Sphere");
sphere_rigid_node->set_mass(2.0);
sphere_rigid_node->add_shape(sphere_shape);
sphere_rigid_node->set_linear_velocity(initialVelBall1); // set the initial
velocity
sphere_rigid_node->set_restitution(1);
physics_world->attach_rigid_body(sphere_rigid_node);
np_sphere = window->get_render().attach_new_node(sphere_rigid_node);
np_sphere.set_pos(0, 0, 0);
np_sphere.set_scale(1.5,1.5,1.5); // set dimension
np_sphere_model = window->load_model(framework.get_models(), "smiley");
np_sphere_model.reparent_to(np_sphere);
}
void init_ball2()
{
initialVelBall2 =(rand()%20-10,rand()%20-10,rand()%20-10);
sphere_shape2 = new BulletSphereShape(1);
sphere_rigid_node2 = new BulletRigidBodyNode("Sphere2");
sphere_rigid_node2->set_mass(1.0);
sphere_rigid_node2->add_shape(sphere_shape2);
sphere_rigid_node2->set_linear_velocity(initialVelBall2);
sphere_rigid_node2->set_restitution(1);
physics_world->attach_rigid_body(sphere_rigid_node2);
np_sphere2 = window->get_render().attach_new_node(sphere_rigid_node2);
np_sphere2.set_pos(2, -1, 2);
np_sphere_model2 = window->load_model(framework.get_models(), "frowney");
np_sphere_model2.reparent_to(np_sphere2);
}
void init_ball3()
{
initialVelBall3 =(rand()%20-10,rand()%20-10,rand()%20-10);
sphere_shape3 = new BulletSphereShape(1);
sphere_rigid_node3 = new BulletRigidBodyNode("Sphere3");
sphere_rigid_node3->set_mass(0.5);
sphere_rigid_node3->add_shape(sphere_shape3);
sphere_rigid_node3->set_linear_velocity(initialVelBall3);
sphere_rigid_node3->set_restitution(1);
physics_world->attach_rigid_body(sphere_rigid_node3);
np_sphere3 = window->get_render().attach_new_node(sphere_rigid_node3);
np_sphere3.set_pos(-2, -1, -2);
np_sphere3.set_scale(0.5,0.5,0.5);
np_sphere_model3 = window->load_model(framework.get_models(), "smiley");
np_sphere_model3.reparent_to(np_sphere3);
}
void init_floor() // make 6 different planes
{
BulletPlaneShape *floor_shape;
BulletRigidBodyNode *floor_rigid_node;
NodePath np_ground;
floor_shape = new BulletPlaneShape(*new LVecBase3f(0, 0, 1), 0); //define
normal
floor_rigid_node = new BulletRigidBodyNode("Ground");
floor_rigid_node->add_shape(floor_shape);
floor_rigid_node->set_restitution(1);
physics_world->attach_rigid_body(floor_rigid_node);
np_ground = window->get_render().attach_new_node(floor_rigid_node);
np_ground.set_pos(0, 0, -4); // define position
BulletPlaneShape *floor_shape1;
BulletRigidBodyNode *floor_rigid_node1;
NodePath np_ground1;
floor_shape1 = new BulletPlaneShape(*new LVecBase3f(1, 0, 0), 0);
//define normal
floor_rigid_node1 = new BulletRigidBodyNode("Ground");
floor_rigid_node1->add_shape(floor_shape1);
floor_rigid_node1->set_restitution(1);
physics_world->attach_rigid_body(floor_rigid_node1);
np_ground1 = window->get_render().attach_new_node(floor_rigid_node1);
np_ground1.set_pos(-4, 0, 0); // define position
BulletPlaneShape *floor_shape2;
BulletRigidBodyNode *floor_rigid_node2;
NodePath np_ground2;
floor_shape2 = new BulletPlaneShape(*new LVecBase3f(-1,
0, 0), 0); //define normal
floor_rigid_node2 = new BulletRigidBodyNode("Ground");
floor_rigid_node2->add_shape(floor_shape2);
floor_rigid_node2->set_restitution(1);
physics_world->attach_rigid_body(floor_rigid_node2);
np_ground2 = window-
>get_render().attach_new_node(floor_rigid_node2);
np_ground2.set_pos(4, 0, 0); // define position
BulletPlaneShape *floor_shape3;
BulletRigidBodyNode *floor_rigid_node3;
NodePath np_ground3;
floor_shape3 = new BulletPlaneShape(*new
LVecBase3f(0, 0, -1), 0); //define normal
floor_rigid_node3 = new
BulletRigidBodyNode("Ground");
floor_rigid_node3->add_shape(floor_shape3);
floor_rigid_node3->set_restitution(1);
physics_world-
>attach_rigid_body(floor_rigid_node3);
np_ground = window-
>get_render().attach_new_node(floor_rigid_node3);
np_ground.set_pos(0, 0, 4); // define position
BulletPlaneShape *floor_shape4;
BulletRigidBodyNode *floor_rigid_node4;
NodePath np_ground4;
floor_shape4 = new BulletPlaneShape(*new
LVecBase3f(0, 1, 0), 0); //define normal
floor_rigid_node4 = new
BulletRigidBodyNode("Ground");
floor_rigid_node4->add_shape(floor_shape4);
floor_rigid_node4->set_restitution(1);
physics_world-
>attach_rigid_body(floor_rigid_node4);
np_ground = window-
>get_render().attach_new_node(floor_rigid_node4);
np_ground.set_pos(0, -4,0 ); // define
position
BulletPlaneShape *floor_shape5;
BulletRigidBodyNode *floor_rigid_node5;
NodePath np_ground5;
floor_shape5 = new BulletPlaneShape(*new
LVecBase3f(0, -1, 0), 0); //define normal
floor_rigid_node5 = new
BulletRigidBodyNode("Ground");
floor_rigid_node5->add_shape(floor_shape5);
floor_rigid_node5->set_restitution(1);
physics_world-
>attach_rigid_body(floor_rigid_node5);
np_ground = window-
>get_render().attach_new_node(floor_rigid_node5);
np_ground.set_pos(0, 4,0 ); // define
position
}
int main(int argc, char *argv[])
{
GenericAsyncTask *task;
NodePath camera;
framework.open_framework(argc, argv);
framework.set_window_title("Bullet Physics");
window = framework.open_window();
// Enable keyboard detection
window->enable_keyboard();
camera = window->get_camera_group();
camera.set_pos(0, -20, 1);
camera.look_at(0, 0, 0);
physics_world = new BulletWorld();
physics_world->set_gravity(0, 0, 0); //set gravity to zero
init_floor();
init_ball1();
init_ball2();
init_ball3();
init_cube();
// define key r for reset
framework.define_key("r","reset",reset,0);
task = new GenericAsyncTask("Scene update", &update_scene, (void*) NULL);
task_mgr->add(task);
framework.main_loop();
framework.close_framework();
return 0;
}
