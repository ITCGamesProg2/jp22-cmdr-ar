![PlantUML Model](./domain_model.png)

collision->Level : collision detection
Player ->Level : render
Enemy->Level : render
Entity->Level : render
Terrain->Level : render
Projectiles->Level : render
Player ->Level : process events
Enemy->Level : process events
Entity->Level : process events
Terrain->Level : process events
Projectiles->Level : process events
Level->Player : collision checking
Level->Enemy: collision checking
Level->Terrain: collision checking
Level->Projectiles: collision checking
HealthBar->Player: displayHealth
HealthBar->Enemy: displayHealth
Editor->Level: create terrain
Editor->Level: create enemies
Level->yaml: save terrain
Level->yaml: save enemies
Level->yaml: load terrain
Level->yaml: load enemies
