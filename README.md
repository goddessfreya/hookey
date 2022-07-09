# Hookey

Enables all the DLCs. Like Creamapi but just for linux and Paradox games.

Works with EU4, HOI4, Stellaris and CK2.

# 1- First, update the dependencies.

Note: If you get SSH errors, make sure your gitlab (not github!) keys are in 
order.


```
$ git submodule update --init --recursive
```
Follow the link below for a guide on setting up your gitlab shh key:

https://docs.gitlab.com/ee/user/ssh.html#adding-an-ssh-key-to-your-gitlab-account


# 2- Add the game

First run the following
```
$ ./add "<game name>" "<path to game>"
```

where `"<game name>"` is lowercase and `"<path to game>"` is the main install directory. E.g.

```
$ ./add "hoi4" "/path/to/your/Hearts-of-Iron-IV"
```

Then select the game you added:

```
$ ./choose 1
```

# 3a- Steam Users

If you bought the game via steam, make sure steam is running in the background.
You won't need steam functional after the install.

Proceed to download the appropriate DLC pack and extract it into the 
`./apps/<game name>/dlc` folder. You might have to create the folder 
if it is not present.

Then run this script:

```
$ ./install_copy
```
Make sure not to run as sudo or root for the script to work properly.

# 3b- Non-steam Users

Otherwise, if your installation already comes with all the DLCs just run this 
script:

```
$ ./install
```

# 3- Waiting... (EU4 Only)

Wait for the launcher to appear, closing it when it does. This might happen
after the install script completes or during.

# 4- Enjoy!

Now, in the future, you can start the game with this command:

``` 
$ ./run 
```

# Hey Gentz, where can I find the DLC packs? 
# Or, hey Gentz, where can I find full game installs?

Google it.

# What about multiple installs?

Good question. You can add multiple game like this:

```
$ ./add "eu4" "$(pwd)/eu4_local"
$ ./add "eu4" "$HOME/.steam/root/steamapps/common/Europa Universalis IV"
$ ./add "ck2" "$(pwd)/ck2_local"
$ ./add "stellaris" "$(pwd)/stellaris_local"
$ ./add "hoi4" "$(pwd)/hoi4_local"
```

You can then select them using the `choose` command. `choose` accepts a number
between 1 and infinity, selecting the nth add. `./install{,_copy}` and `./run`
will operate on you're chosen game. You can confirm you chose the right game
because choose will output your selection. E.g:

```
$ ./choose 2
[...]
eu4 /home/gentz/.steam/root/steamapps/common/Europa Universalis IV

$ ./run
[Runs eu4]

$ ./choose 1
[...]
eu4 /home/gentz/Documents/hookey /hookey/eu4_local

$ ./install
[Installs that other eu4]

$ ./run
[Runs that other eu4]
```

# What about my achievements?

While the previous Hookey supported achievements because it only intercepted a 
subset of the Steamworks API, the new Hookey does not.

We have switched to Mr_Goldberg's wonderful Goldberg Emulator, as that's a 
lesser maintenance burden on my poor soul. Goldberg Emulator, unlike the old 
Hookey, completely emulates the Steamworks API, and does not support 
achievements.

I personally never cared all too much for achievements, so so be it.

This comes with some benefits, of course. Now Steam is not required to run in 
the background!


# I am having issues running the installation!

First, make sure to check all errors when running; they provide the best clues to your issue. Here are a few suggestions on commonly encountered errors:
###### "libc.so.6" errors
- Make sure your `libc.so.6` file is present in your `/usr/lib/` directory, and that the `hookey/app/${APP}/run` file is correctly pointing to the correct lib.so.6 file.
###### "Launcher not found, retrying" error
- Ensure the variable `LAUNCHER_API_LOC` in your `hookey/app/${APP}/common` is pointing to the correct location for your paradoxlauncher, and that the version is correct.
###### "protoc and make" error
- Make sure to install the protobuf-compiler library using `sudo apt-get install protobuf-compiler`
