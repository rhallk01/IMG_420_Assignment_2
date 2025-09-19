extends CharacterBody2D


@export var speed = 200.0
@export var jump_force = -275.0
@export var gravity = 20.0

@onready var ap = $AnimationPlayer
@onready var sprite = $Sprite2D
@onready var c_shape = $CollisionShape2D
@onready var c_raycast1 = $raycast_1
@onready var c_raycast2 = $raycast_2

signal game_over

var is_crouched = false
var tall_c_shape = preload("res://resources/collision_shape_tall.tres")
var short_c_shape = preload("res://resources/collision_shape_short.tres")
var hitting_head_state = false
var can_move = true

func _ready() -> void:
	can_move = false
	add_to_group("Player")
	add_to_group("PlayerChar")
  
	
func update_animations(horizontal_direction):	
	if is_on_floor():
		if horizontal_direction == 0:
			if is_crouched:
				ap.play("crouch_idle")
			else:
				ap.play("idle")
		else:
			if is_crouched:
				ap.play("crouch_walk")
			else:
				ap.play("run")
	else:
		if not is_crouched:
			if velocity.y > 0:
				ap.play("fall")
			else:
				ap.play("jump")
		else:
			ap.play("crouch_idle")			

func _get_direction(_delta) -> int:
	return Input.get_axis("move_left", "move_right")
	
func switch_direction(horizontal_direction):
	sprite.flip_h = (horizontal_direction == -1)
	sprite.position.x = horizontal_direction * -2

func crouch():
	if is_crouched:
		return
	is_crouched = true
	c_shape.shape = short_c_shape
	c_shape.position.y = -10
	
func stand():
	if not is_crouched:
		return
	is_crouched = false
	c_shape.shape = tall_c_shape
	c_shape.position.y = -15
	
func not_hitting_head() -> bool:
	return not c_raycast1.is_colliding() and not c_raycast2.is_colliding()

func _physics_process(delta):
	if not can_move:
		velocity = Vector2.ZERO
		move_and_slide()
		return
	if not is_on_floor():
		velocity.y += gravity
		if velocity.y > 1000:
			velocity.y = 1000
			game_over.emit()

	if Input.is_action_just_pressed("jump") and is_on_floor():
		velocity.y = jump_force

	var horizontal_direction := _get_direction(delta)
	if horizontal_direction != 0:
		switch_direction(horizontal_direction)
		
	if horizontal_direction:
		velocity.x = horizontal_direction * speed
	else:
		velocity.x = speed * horizontal_direction
			
	if Input.is_action_just_pressed("crouch"):
		crouch()
	elif Input.is_action_just_released("crouch"):
		if not_hitting_head():
			stand()
		else:
			hitting_head_state = true
	if hitting_head_state and not_hitting_head() and not Input.is_action_pressed("crouch"):
		stand()
		hitting_head_state = false

	move_and_slide()
	
	update_animations(horizontal_direction)
	
