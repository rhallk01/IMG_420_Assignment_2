extends Area2D
signal killedByFire

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta: float) -> void:
	pass


func _on_fire_guy_died_by_flame(_body: Object) -> void:
	await get_tree().create_timer(0.2).timeout
	killedByFire.emit()
