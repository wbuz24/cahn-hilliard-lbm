## For Price

Hey Price, I am just leaving this here as a few notes if the code comments aren't doing enough.

# Where am I right now?

I am trying to finish the domain initialization and I need to test that my readcsv function appropriately applies a domain from a file. Then I will flip the bits at the boundaries to 1 to indicate a solid at that location. 

# The header file is ambiguous

Remember, you have complete control of your class and function definitions, this isn't a lab but almost like designing your own - if you don't have something i have written for you, give it to yourself.

My header file and node definitions are currently built to be digestible when you get into the real LBM functions and how they stream information between lattice nodes. 

My current idea is to make a node class definition fit the definiton of an LBM lattice node. On top of that, LBM lattice nodes often care about their neighbors and much of the structure of LBM depends on the behavior and setup of the lattice structure. This is an interesting opportunity for someone with lots of computer science knowledge - I recommend looking into Stephen Wolfram's cellular automata (this is the basis of LBM and much of the "partical theory" that LBM is built on), you are also familiar with Wolfram from Wolfram Alpha, the online calculator. The connection here is through the opportunity to mimic the lattice structure and theory within your code. The lattice node parallels beautifully with an appropriate node class data structure.

# Next steps

copy the domain.txt from the python repo, read it and print the entire domain. Check with Frida and move forward from there trying to stick as close as possible to the python code.

# Parallelism

What I have learned from 360: threading and multi-processes are weird, they aren't exactly what you think and it is a different beast to manipulate them to run parallel. Frida has some knowledge of how to do this from her courses, but in classical computer science multi-processes are really built in for catching "asynchronous actions" think keyboard clicking while something is running. You want your program to have a core available to catch and process the keys while your main core continues to run. This is very helpful for scheduling and signal catching, and as mentioned can be manipulated for parallelism - which is your goal here. 

Keep this in mind when you cross that bridge and don't be afraid to reach out for help.
