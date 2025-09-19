#include "fireguy.h"
#include <godot_cpp/core/class_db.hpp>


using namespace godot;

void FireGuy::_bind_methods() {
	// all of the bing methods for speed, height, and on_body_enetered
	ClassDB::bind_method(D_METHOD("get_speed"), &FireGuy::get_speed);
	ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &FireGuy::set_speed);

	ClassDB::bind_method(D_METHOD("get_height"), &FireGuy::get_height);
	ClassDB::bind_method(D_METHOD("set_height", "p_height"), &FireGuy::set_height);

	ClassDB::bind_method(D_METHOD("get_flame_radius"), &FireGuy::get_flame_radius);
	ClassDB::bind_method(D_METHOD("set_flame_radius", "p_radius"), &FireGuy::set_flame_radius);

	ClassDB::bind_method(D_METHOD("on_body_entered", "body"), &FireGuy::on_body_entered);
	ClassDB::bind_method(D_METHOD("_on_signal_emitted"), &FireGuy::_on_signal_emitted);

	// add properties for speed and height so they're available in editor
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "track_height"), "set_height", "get_height");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "flame_radius"), "set_flame_radius", "get_flame_radius");


	// add signals for diedByFlame when the player touches one of it's collision shapes
	ADD_SIGNAL(MethodInfo("diedByFlame", PropertyInfo(Variant::OBJECT, "body")));
}

FireGuy::FireGuy() {
	// initialize variables
	time_passed = 0.0;
	Vector2 start_pos = get_position();
	speed = 20.0;	
	direction = 1;
	initial_position_y = start_pos.y;
	track_height = 100.0;
	death_num = 0;
	flame_radius = 16;
	//make collision shapes for the fire guy and the fire he 'breathes'
		//set the area2ds
	hit_1 = memnew(Area2D);
	hit_2 = memnew(Area2D);
		//set the collision shapes
	collision_shape_1 = memnew(CollisionShape2D);
	collision_shape_2 = memnew(CollisionShape2D);
		//set the shape for the collision shapes to be 16px radius circles
	Ref<CircleShape2D> shape1 = memnew(CircleShape2D);
	shape1->set_radius(16);
	collision_shape_1->set_shape(shape1);
	
	Ref<CircleShape2D> shape2 = memnew(CircleShape2D);
	shape2->set_radius(flame_radius);
	collision_shape_2->set_shape(shape2);
			//set the position of the flame to be 60 px left of the sprite
	collision_shape_2->set_position(Vector2(-60, 0));

	//add the collision shapes to the area2ds
	hit_1->add_child(collision_shape_1);
	hit_2->add_child(collision_shape_2);

	//add the area2ds
	add_child(hit_1);
	add_child(hit_2);

	//set up the fire guy and fire textures
	//set up animation for the fire guy
		//for the fire, just make a 2d sprite, load it with the fire png, 
		//and set its position to the left pf the fire guy
	sprite_node = memnew(Sprite2D);
    Ref<Texture2D> my_texture = ResourceLoader::get_singleton()-> load("res://assets/fire_singular.png");
    sprite_node->set_texture(my_texture);
	sprite_node->set_position(Vector2(-60, 0));
	sprite_node->show();
	sprite_node->set_scale(Vector2(flame_radius/20, flame_radius/20));
	//add the sprite2d
	add_child(sprite_node);

	//set up the animated sprite2d for the fire guy
		//set its texture as a .tres file I made for the sprite frames
		//set the frames as the .tres resource
		//set the animation, play it, flip it so its looking to the left, and show it
	animated_sprite = memnew(AnimatedSprite2D);
	Ref<SpriteFrames> frames = ResourceLoader::get_singleton()->load("res://assets/flame_guy.tres");
	animated_sprite->set_sprite_frames(frames);
	animated_sprite->set_animation("flame");
	animated_sprite->play("flame");
	animated_sprite->set_flip_h(true);
	animated_sprite->show();
	//add the animated sprite2d
	add_child(animated_sprite);

	//set up the dynamic label for the sprite, this will change depending on how many 
	//deaths the player has had, responding to the game_over signal from the Player scene
	//and the diedByEnemy signal from the Enemy scene
	label = memnew(Label);
	Ref<Font> font = ResourceLoader::get_singleton()->load("res://assets/EagleLake-Regular.ttf");
	label->set_position(Vector2(-30, -65));
	label->add_theme_font_override("font", font);
    label->add_theme_font_size_override("font_size", 5);
	label->add_theme_constant_override("line_spacing", .6); 
	label->set_text("Enemy, don't touch!!\nWatch for fire!\nMaybe you can do it first try!");
	add_child(label);
	
}

void FireGuy::_ready() {
	//set up listening for the game over signal from Player scene
	//if heard, call on_signal_emitted function to update the label
	Node *player = get_node<Node>("/root/World/Player");
	if (player) {
		player->connect("game_over", Callable((Object *)this, "_on_signal_emitted"));
	}
	//set up listening for the died by enemy signal from Enemy scene
	//if heard, call on_signal_emitted function to update the label
	Node *enemy = get_node<Node>("/root/World/Enemy");
	if (enemy) {
		enemy->connect("diedByEnemy", Callable((Object *)this, "_on_signal_emitted"));
	}

	//set up listening for either of the collision shapes to be hit (body_entered)
	//if this occurs, call on_body_entered function
	if (hit_1 && hit_2) {
		hit_1->connect("body_entered", Callable(this, "on_body_entered"));
		hit_2->connect("body_entered", Callable(this, "on_body_entered"));
	} else {
		UtilityFunctions::print("Warning: hit areas not initialized.");
	}
}


FireGuy::~FireGuy() {
	// Add your cleanup here.
}

void FireGuy::_process(double delta) {
	//get the current position of the fire guy
	Vector2 current_pos = get_position();
	//initialize bool within_range as false
	bool within_range = false;

	//for context: the initial position is the top of the track, the bottom is 
	//at the initial position+track height (which is lower, bigger numbers are lower down)


	//if the current y is less than the initial position (ie ABOVE initial position)
	//switch to going down
	if (current_pos.y <= initial_position_y)
		{ direction = 1; }
	//if the current y is greator than the initial position+track height (ie BELOW initial position+track height)
	//switch to going up
	if (current_pos.y >= initial_position_y + track_height)
		{ direction = -1; }

	//set top and bottom of range for when 'breathing' fire
	//top is middle of the track +20, bottom is middle of the track -20
	double top_of_range = initial_position_y + track_height/2 + 20;
	double bottom_of_range = initial_position_y + track_height/2 - 20;

	//only 'breathe' fire when going down (direction = 1) so it isn't too hard
	if (direction == 1) {
		//set bool within range by evaluating if position is between top and bottom of range
		within_range = current_pos.y >= bottom_of_range && current_pos.y <= top_of_range;
		//set collision shape disabled if not in range, else set enables
		collision_shape_2->set_disabled(!within_range);
		//if within range, show the fire texture and emit the watch for fire signal
		if (within_range){
			sprite_node->show();	
		}
		//else, hide the fire texture
		else
			sprite_node->hide();
	}
	//create new position with same x and new y
	Vector2 new_position = Vector2(
		current_pos.x,
		current_pos.y + (delta*speed*direction)
	);
	//set this new position
	set_position(new_position);
	
}

//set speed 
void FireGuy::set_speed(const double p_speed) {
	speed = p_speed;
}
//get speed 
double FireGuy::get_speed() const {
	return speed;
}
//set height for track 
void FireGuy::set_height(const double p_height) {
	track_height = p_height;
}
//get height for track
double FireGuy::get_height() const {
	return track_height;
}
//set radius for fire being 'breathed'
void FireGuy::set_flame_radius(const double p_radius){
	flame_radius = p_radius;
}
//get radius for fire being 'breathed'
double FireGuy::get_flame_radius() const {
	return flame_radius;
}


//when the signals diedByEnemy or game_over are emitted
//this function is called to change the label of the fire guy
void FireGuy::_on_signal_emitted() {

	//iterate death count (death_num) by 1
	death_num ++;

	//switch label based on how many deaths the player has had
	if (death_num >0 && death_num<5){
		label->set_text("Enemy, don't touch!!\nWatch for fire!\nYou haven't died much yet!");
	}else{
		label->set_text("Enemy, don't touch!!\nWatch for fire!\nYou've already died alot!");
	}
	
}
//when either collision shape is entered, this function is called
void FireGuy::on_body_entered(Node *body) {
	//if the body that entered is the player, emit the diedByFlame signal
	if (body->is_in_group("PlayerChar")) {
		UtilityFunctions::print("Player entered!");
		emit_signal("diedByFlame", body);
	}	
}