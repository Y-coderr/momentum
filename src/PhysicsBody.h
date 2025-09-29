#pragma once
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <memory>
//for poointing the vertex data

enum BoundingType {CUBE , SPHERE,CUBOID ,CAPSULE};

struct AxisBox {
	Eigen::Vector3f vMax , vMin;
};

//MERE ENGINE ME ACTUAL SHAPE SE HI COLLISON DETECT HOGA NOT ARTIFICAL SHAPE [ UNTILL I CHANGE MY MIND]
//for non Collidable body
class Body
{
protected:
	Eigen::Matrix4f Transform;
	Eigen::Vector3f Position;
	Eigen::Vector3f Scale;
	Eigen::Vector4f Rotation;
	//for cuboid ,capcule , sphere

public:
	BoundingType Collider;
	//in C++ the constructor of Parent is called when we create an Child Object
	Body( BoundingType type);//required so we know whats the bb type
	~Body();

	void setPosition(const Eigen::Vector3f&);
	void Translate(const Eigen::Vector3f&);
	Eigen::Vector3f getPosition()const;

	//syncs with Collider also
	void setScale(const Eigen::Vector3f);
	//only Updates Entity Scale
	Eigen::Vector3f getScale()const;
	//for accessing the data in collision detect for specially cuboid ,capsule,sphere and for renderer raw data
	float getScale_X()const {
		return Scale.x();
	}
	float getScale_Y()const {
		return Scale.y();
	}
	float getScale_Z()const {
		return Scale.z();
	}


	AxisBox getAABBbox()const;

	float* ConstructTransformMat();
	virtual void Update(float deltaTime, const float gravity){}
	virtual Eigen::Vector3f getVelocity()const { return Eigen::Vector3f::Zero(); }//yaha mene null vector send kiya keep that in mind
	virtual float getInverseMass()const { return 0.0f; }
	virtual void ApplyImpulse(const Eigen::Vector3f, const float deltaTime){}
};
//for body which is Collidable
class PhysicsBody :public Body 
{
protected:
    float Mass;
    float Restitution;      // Coefficient of restitution (0 = inelastic, 1 = perfectly elastic)
    float FrictionStatic;   // Static friction coefficient
    float FrictionDynamic;  // Dynamic friction coefficient
    Eigen::Vector3f Velocity;
    Eigen::Vector3f Force_accumulator;
    Eigen::Vector3f Angular_velocity;
    Eigen::Vector3f Torque_accumulator;
    bool Influence_gravity;
    bool IsAsleep;          // For optimization: bodies at rest

public:
    PhysicsBody(bool gravity_influence, float mass, BoundingType type);
    ~PhysicsBody();

    // Core physics update methods
    void Update(float deltaTime, const float gravity) override;
    void ApplyImpulse(const Eigen::Vector3f impulse, const float deltaTime) override;
    float getInverseMass() const override { return Mass > 0 ? 1/Mass : 0.0f; }

    // Velocity and force methods
    Eigen::Vector3f getVelocity() const override { return Velocity; }
    void ApplyForceAtPoint(const Eigen::Vector3f force, const Eigen::Vector3f point);
    void setVelocity(const Eigen::Vector3f& vel) { Velocity = vel; }

    // Material properties
    float getRestitution() const { return Restitution; }
    void setRestitution(float e) { Restitution = std::clamp(e, 0.0f, 1.0f); }
    
    float getFrictionStatic() const { return FrictionStatic; }
    void setFrictionStatic(float f) { FrictionStatic = std::max(0.0f, f); }
    
    float getFrictionDynamic() const { return FrictionDynamic; }
    void setFrictionDynamic(float f) { FrictionDynamic = std::max(0.0f, f); }

    // Sleep state management
    bool isAsleep() const { return IsAsleep; }
    void setAsleep(bool asleep) { IsAsleep = asleep; }
    
    // Force accumulator management
    void clearForces() { Force_accumulator.setZero(); Torque_accumulator.setZero(); }
};


