extends Area2D

signal game_won
signal show_won
signal need_key

var hasKey = false
@onready var ap = $AnimationPlayerChest

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	ap.play("closed")
	$Flower.hide()

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta: float) -> void:
	pass


func _on_body_entered(_body: Node2D) -> void:
	if hasKey == true:
		ap.play("open")
		show_won.emit()
		$ChestLabel.hide()
		$ChestLabel/arrow.hide()
		$Flower.show()
		await get_tree().create_timer(1.15).timeout
		game_won.emit()
	else:
		need_key.emit()
