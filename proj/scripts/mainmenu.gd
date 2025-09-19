extends CanvasLayer

signal start_game

func _ready() -> void:
	$WinOrLose.hide()
	
func show_message(text):
	$Message.text = text
	$Message.show()
	$Message2.text = text
	$Message2.show()


func show_game_over():
	$WinOrLose.text = "GAME OVER"
	show()
	$WinOrLosebg.show()
	$WinOrLose.show()
	await get_tree().create_timer(.6).timeout
	$WinOrLose.hide()
	$WinOrLosebg.hide()
	$MainMenubg.show()
	$Message.text = "The Legend of Autumn"
	$Message.show()
	$Message2.text = "get the key and\nopen the chest to win...\ndie to lose!"
	$Message2.show()
	$StartButton.show()
	
func show_game_won():
	$WinOrLose.text = "YOU WON!!"
	$WinOrLose/howDie.hide()
	show()
	$WinOrLosebg.show()
	$WinOrLose.show()
	await get_tree().create_timer(1).timeout
	$WinOrLose.hide()
	$WinOrLosebg.hide()
	$MainMenubg.show()
	$Message.text = "The Legend of Autumn"
	$Message2.text = "get the key and\nopen the chest to win...\ndie to lose!"
	$Message.show()
	$Message2.show()
	$StartButton.show()

func _on_start_button_pressed():
	$MainMenubg.hide()
	$StartButton.hide()
	$Message.hide()
	$Message2.hide()
	start_game.emit()
