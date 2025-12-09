why configuration management tools are mutable and provisioning tools are immutabe?

when new changes are update in tools such as ansible, they are updated on an existing server i.e new changes are stacked one after another which creates a history of changes in the system which could create server specific problems

on the other hand, when using tools such as terraform, then those changes are updated to a completely new server, the old servers are then destroyed