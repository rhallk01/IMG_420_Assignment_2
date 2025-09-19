#ifndef FIREGUY_H
#define FIREGUY_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/rectangle_shape2d.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/circle_shape2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/font_file.hpp>

namespace godot {

class FireGuy : public Sprite2D {
	GDCLASS(FireGuy, Sprite2D)

private:
	//declare private variables
	double time_passed;
	double speed;
	double track_height;
	double flame_radius;
	double initial_position_y;
	int direction;
	int death_num;
	Vector2 start_pos;
	CollisionShape2D* collision_shape;
	Sprite2D* sprite_node = nullptr;
	Sprite2D* sprite_node1 = nullptr;

	Area2D *hit_1 = nullptr;
	Area2D *hit_2 = nullptr;
	CollisionShape2D *collision_shape_1 = nullptr;
	CollisionShape2D *collision_shape_2 = nullptr;	
	AnimatedSprite2D* animated_sprite = nullptr;

	Label *label = nullptr;


protected:
	static void _bind_methods();

public:
	//declare functions
	FireGuy();
	~FireGuy();

	void _process(double delta) override;
	void set_speed(const double p_speed);
	void set_height(const double p_height);
	void set_flame_radius(const double p_radius);

	double get_speed() const;
	double get_height() const;
	double get_flame_radius() const;

	void _ready() override;
	void _on_signal_emitted();
	void on_body_entered(Node *body);
};

}

#endif