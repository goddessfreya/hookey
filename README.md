# Hookey

Enables all the EU4 DLCs. Like Creamapi but just for linux and EU4.

First:
```
$ git submodule update --init --recursive

$ echo "<directory where EU4 is placed>" > .eu4_location
```

If you bought the game via steam, make sure steam is running in the background.

Proceed to download
[this](https://cs.rin.ru/forum/viewtopic.php?p=1973047#p1973047) DLC pack and
extract it into the "./dlc" folder. You might have to create the folder if it 
is not present.

Then run this script:

```
$ ./install_copy
```

Otherwise, if your installation already comes with all the DLCs (as in, you got
it from [here](https://cs.rin.ru/forum/viewtopic.php?f=22&t=54230)) just run
this script:

```
$ ./install
```

Wait for the launcher to appear, closing it when it does.

Now in the future, you can start the game with this command, even if steam is
not running:

``` 
$ ./run 
```
