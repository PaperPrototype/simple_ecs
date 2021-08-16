Each node holds a differnt type of component. (although I changed it so that each node is an array of components).

The goal was to have each node hold an unknown type. I got that working. I then changed the code to try and support having an array of components in each node (as oppesd to a single component). This eventually leaded to a seg fault, and so I started over.