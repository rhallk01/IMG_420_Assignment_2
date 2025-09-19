extends Area2D

signal got_key

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	show()


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta: float) -> void:
	pass


func _on_body_entered(_body: Node2D) -> void:
	hide()
	got_key.emit()
