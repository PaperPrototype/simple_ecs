Now I store an array of generic arrays. Each generic array is wrapped in an "aspect" struct. The aspect struct has a "type name". Currently we are not using the "type" in the aspect struct. Later we will search through an array of aspects, checking their "type". 

Technically at this point an array of aspects is basically an archetype.