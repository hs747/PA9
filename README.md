# PA9
## Information
* Right now, the project can only be built and run on Windows

## Configuration for debugging
1. Select the project you want to run (PA9Main for now).
2. Go to project>properties>'TheProject' Properties
3. In the properties editor, set the Configuration dropdown to Debug and set the Platform to Win32.
4. Keeping those configuration options set, go to ConfigurationProperties>Debugging and in the Environment field, enter the field below. This is so the DLLS get loaded when debugging without having to copy them everytime:
```
PATH=$(SolutionDir)SFML-2.5.1\bin;%PATH%
```
5. All the other configurations should already be set and tracked in the repo, so you should be able to run the project in the local debugger and use all the SFML libraries dynamically.

## Building for release
TODO

## Git workflow (for Henry, Korbin, Chase)
* https://www.atlassian.com/git/tutorials/comparing-workflows#centralized-workflow
* We should probably use the main branch as a backup / mostly finished stuff branch.
* For now just use the dev branch to edit the project, and we will occasionally merge stuff we think is finalized into the main branch. Make sure you are checked out of the dev branch.
* When you begin working (like when you open the project for the 1st time in the day), or if you are starting a new feature, pull from dev.
* When you are done working (probably at the end of the day), and you think the changes you made should be shared with the rest of us, or if you have a complete feature, first do a pull, resolve any merge conflicts (try to make sure the program still works correctly when doing this), then push.

## Project planning
* Will need a folder, probably inside the project folder for resources like textures, fonts?, sounds.
* Will need a resource manager singleton in the program that, at a minimum maintains unique instances of all textures (refer to SFML docs on the texture class)
* Might need a generic sprite / scene rendering system
* Will probably need a collision handling system, possibly raycasting, (probably not physics).
* Might need a tile system?