
#include <iostream>

#include <rbdl.h>

using namespace RigidBodyDynamics;
using namespace RigidBodyDynamics::Math;


int test()
{
	
	Model* model = new Model;
	model->Init();
	model->gravity = Vector3d (0., -9.81, 0.);
	
	Body base = Body (1., Vector3d (1., 0., 0.), Vector3d (1., 1., 1.));

	
	unsigned int base_body_id = model->SetFloatingBaseBody(base);
	VectorNd q, qdot, qddot, tau;
	
	q = VectorNd::Constant(model->dof_count, 0.);
	qdot = VectorNd::Constant(model->dof_count, 0.);
	qddot = VectorNd::Constant(model->dof_count, 0.);
	tau = VectorNd::Constant(model->dof_count, 0.);
	
	q[1] = 1.;
	ForwardDynamics (*model, q, qdot, tau, qddot);
	
	Vector3d test_point;
	
	test_point = CalcBaseToBodyCoordinates (*model, q, base_body_id, Vector3d (0., 0., 0.), false);
	
	VectorNd Q = VectorNd::Zero (model->dof_count);
	VectorNd QDot = VectorNd::Zero (model->dof_count);
	VectorNd QDDot = VectorNd::Zero (model->dof_count);
	VectorNd Tau = VectorNd::Zero (model->dof_count);
	
	unsigned int ref_body_id = base_body_id;

	
	QDot[0] = 1.;
	Vector3d point_position(1., 0., 0.);
	Vector3d point_velocity;
	
	point_velocity = CalcPointVelocity(*model, Q, QDot, ref_body_id, point_position);

	
	/*
 Model* model = NULL;

        unsigned int body_a_id, body_b_id, body_c_id;
        Body body_a, body_b, body_c;
        Joint joint_a, joint_b, joint_c;

        model = new Model();
        model->Init();

        model->gravity = Vector3d (0., -9.81, 0.);

        body_a = Body (1., Vector3d (0.5, 0., 0.0), Vector3d (1., 1., 1.));
                joint_a = Joint(
                JointTypeRevolute,
                Vector3d (0., 0., 1.)
        );

        body_a_id = model->AddBody(0, Xtrans(Vector3d(0., 0., 0.)), joint_a, body_a);

        body_b = Body (1., Vector3d (0., 0.5, 0.), Vector3d (1., 1., 1.));
                joint_b = Joint (
                JointTypeRevolute,
                Vector3d (0., 0., 1.)
        );

        body_b_id = model->AddBody(body_a_id, Xtrans(Vector3d(1., 0., 0.)), joint_b, body_b);

        body_c = Body (0., Vector3d (0.5, 0., 0.), Vector3d (1., 1., 1.));
                joint_c = Joint (
                JointTypeRevolute,
                Vector3d (0., 0., 1.)
        );

        body_c_id = model->AddBody(body_b_id, Xtrans(Vector3d(0., 1., 0.)), joint_c, body_c);

        VectorNd Q = VectorNd::Zero (model->dof_count);
        VectorNd QDot = VectorNd::Zero (model->dof_count);
        VectorNd Tau = VectorNd::Zero (model->dof_count);
        VectorNd QDDot = VectorNd::Zero (model->dof_count);

        ForwardDynamics (*model, Q, QDot, Tau, QDDot);

        std::cout << QDDot.transpose() << std::endl;

        delete model;
*/
	
        return 0;

}
