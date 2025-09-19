extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta: float) -> void:
	if $Player.position.x > -20 && $Player.position.x < 90:
		$HUD_tutorial/MoveKeyLabel.show()
	else:
		$HUD_tutorial/MoveKeyLabel.hide()

func new_game():
	$HUD_tutorial/keyStatus.text = "you need\nthe key"
	$Chest.hasKey = false
	$HUD_tutorial/YouWin.hide()
	$MainMenu.hide()
	$HUD_tutorial/BoostMessage.hide()
	$JumpBoost.show()
	$Key.show()
	$Player.speed = 200.0
	$Player.jump_force = -275.0
	$Player.can_move = true

func _on_player_game_over() -> void:
	$MainMenu/WinOrLose/howDie.text = "you fell to your death"
	game_over()
	
func game_over() -> void:
	$Player.set_physics_process(false)
	$Player.global_position = Vector2(80, 150)
	$Player.velocity = Vector2.ZERO
	$Player.set_physics_process(true)
	$Player.can_move = false
	$DeathSound.play()
	$MainMenu.show_game_over()


func _on_jump_boost_boost() -> void:
	$JumpBoost.hide()
	$Player.jump_force = -350.0
	$HUD_tutorial/BoostMessage.text = "5 sec jump boost!"
	$HUD_tutorial/BoostMessage.show()
	await get_tree().create_timer(5.0).timeout
	$Player.jump_force = -275.0
	$HUD_tutorial/BoostMessage.text = "jump boost over"
	await get_tree().create_timer(1.0).timeout
	$HUD_tutorial/BoostMessage.hide()


func _on_enemy_died_by_enemy() -> void:
	$MainMenu/WinOrLose/howDie.text = "you were killed by the enemy"
	game_over()


func _on_chest_game_won() -> void:
	$Player.set_physics_process(false)
	$Player.global_position = Vector2(80, 150)
	$Player.velocity = Vector2.ZERO
	$Player.set_physics_process(true)
	$Player.can_move = false
	$Chest.ap.play("closed")
	$Chest/Flower.hide()
	$HUD_tutorial/YouWin.hide()
	$Chest/ChestLabel.hide()
	$Chest/ChestLabel/arrow.show()
	$MainMenu.show_game_won()


func _on_main_menu_start_game() -> void:
	$MainMenu.hide()
	$HUD_tutorial/BoostMessage.hide()
	$JumpBoost.show()
	$Player.speed = 200.0
	$Player.jump_force = -275.0
	$Player.can_move = true


func _on_chest_show_won() -> void:
	$HUD_tutorial/YouWin.show()
	$HUD_tutorial/BoostMessage.hide()


func _on_key_got_key() -> void:
	$HUD_tutorial/keyStatus.text = "you have\nthe key"
	$Chest.hasKey = true
	


func _on_chest_need_key() -> void:
	$HUD_tutorial/GetTheKey.show()
	await get_tree().create_timer(.4).timeout
	$HUD_tutorial/GetTheKey.hide()
