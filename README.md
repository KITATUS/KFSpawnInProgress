Today, we are going to look at how we can deal with spawning friendly players in a co-operative game. First, we will look at the pseudo-code and then how we can achieve said functionality in Blueprints and then C++. 

One thing you have to keep in mind when spawning players in a co-operative game is that they might join after the game has already started, so we want a system that doesn't judge if a player is right then when the game begins or if they join afterwards.

We are going to leverage the Game Mode class for this, as the Game Mode handles important things such as when players join the game, the numbers of player required to play .etc and is not replicated to remote clients (it only exists on the server). As we are dealing with players joining the game, this is definately the right place.

## Psuedo-Code
The basic idea behind the code we're going to need is as so:

Within the game mode; when a player joins, check if they have a pawn. If they don't, they haven't already been spawned. So let's find the first player we can spawn near them. If we don't find one, let's find a player start placed in the world somewhere and use the transform for that instead. 

By now, we have a spawn transform to use, so lets use that and spawn the new player character. Spawn the player with a random offset on the X and Y.Once the character has been spawned, tell the new controller to possess it and then we should fire off an intialize on it.

The reason behind the Initialize event would be to do everything that you'd normally do in the BeginPlay (such as locally setting the camera for a player) as it might not have been ready yet as the player didn't immediately possess it.

## Blueprint
Let's first look at how we would implement this in Blueprint. Inside the GameMode blueprint, we have hooked into the function for  ```HandleStartingNewPlayer``` by adding the Blueprint exposed event for it. From where, we pass into a custom function;  ```SpawnMPChar``` , which takes in the PlayerController output from   ```HandleStartingNewPlayer```.

Inside  ```SpawnMPChar``` we first check if this player already has a pawn. In the use case of this example, either they have the character ready or they don't but in your use case, you might want to further check if the character they have is the character you want them to have or if some variables need to be setup on said character, you could use this to confirm that character is in a state you want it to be.

**Note:** Did you know that you can reference inputs from functions in Blueprint without having to have wires everywhere? Once the function has been created, compile and save then when you open the "All actions for this Blueprint Window" (usually by right clicking), you can find and use the variable!

If the player controller doesn't have an accociated character, we need to create them one.

We clear our the SpawnTransform to ensure we're not accidently overwriting any existing data (normally this won't be the case but it doesn't hurt to be careful!) then we try and find an existing character in the scene (to spawn beside). We grab the first value that comes back from the  ```GetAllActorsOfClass```  node and check to see if it returned valid or if we didn't find anything.

**Note:** If you were dealing with a game where you only wanted people to spawn at a player location if certain criteria were met; such as location they were at or what team they're on - this would be the perfect time to do it.

If we actually found a player, we're going to get their transform and use it. If we didn't find a player (i.e the temporarily stored variable is null), we'll instead look for a PlayerStart and use the transform of that.

Once we have a SpawnTransform, we break it apart to add some random variation. This is so if we have multiple people spawning, the chances of them spawning the exact same spot are significantly lower.

Once we have set the SpawnTransform to a more appropriate value, we then simply spawn the Character and tell the PlayerController (variable input of this function) to possess that created character.

...And that's all there is to it! If we open this map using ``` Open Map_Example01?listen``` and we join the match once it has started, you can see that we spawn by the player and are ready to go on a co-operative adventure with them!

As previously explained, if you have custom code that needs to run locally on a client on Begin Play, it's probably a good idea to create a "Initialize" function and do it there instead - calling it after the Possess. Alternatively, you could also use the OnPossessed event within the Character Blueprint.

Now, let's see how we would approach this in C++.

## C++
Inside the GameMode class, ```GM_Example02.h``` overrides the ``` HandleStartingNewPlayer ``` similar to how we did in Blueprint. The main difference in C++ is the fact that ```HandleStartingNewPlayer``` is a BlueprintNativeEvent, meaning that if we wish to override it in C++, we actually have to override the "Implementation" of it by using ```Class_Implementation```.

With ``HandleStartingNewPlayer``` overriden in the .h, let's look at the implementation itself.

If we dive into the function; you'll notice that we do pretty much everything we did in the Blueprint, with the addition of a few minor C++ things in addition to one key change to before.

First up, we're checking if the player coming in already has a pawn, specifically (this time) if they have an Example02Char. If they do, we don't need to do anything but if they don't we now check to see if they have a pawn that isn't Example02Char. If they do, we don't want that so let's destroy it.

Now we've got a blank slate to spawn them an Example02 character. From here, we try and find any characters that already exist in the map. If we find on, we use their Transform and if not, we find the PlayerStart and use the transform for that.

With SpawnTransform in hand, we apply our X and Y variations just like we did in the Blueprint.


Finally, we spawn the player and tell the controller to possess it - just like before.

...And that's it! The player will now spawn at a PlayerStart if they're not Example02 character (and there's no Example02 character in the scene) or it will spawn alongside their co-operative buddy.

## Extras

### Written Page (With Images)
[KITATUS.github.io](https://kitatus.github.io/ue4/ue5/blueprints/c++/networking/joininprogress/)
