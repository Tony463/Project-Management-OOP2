# Project Management Application


## Description

The project management application found in this repo has some simple functionalities which have the following concepts under the hood:

- hierarchical inheritance (we have a pure virtual class Resource and 2 classes which inherit from it: SoftwareResource and LaborResource and a pure virtual class Task and 3 classes which inherit from it: BugTask, FeatureTask, ResearchTask)
- runtime polymorpishm through virtual methods (we have virtual methods for reading, writing and calculating cost based on different types of tasks) - the instances of dynamic dispatch and upcasting were commented in the code
- exceptions (a custom exception is defined and thrown in a try catch block, printing a specific message)
- static member variable (we use it to count the number of created projects)



