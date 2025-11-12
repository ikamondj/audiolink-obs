This is a two part plugin. obs-shader-filter is an existing plugin that lets you write any shaders as a filter for your obs source.
audiolink is a separate plugin that feeds audio data to this modified shader filter plugin
To install obs-shader-filter, just run the obs-shader-filter installer. 
From what I've seen this doesn't break existing shader filters setups (but this plugin is not production tested. PLEASE BACK UP YOUR OBS SCENES FIRST)
To install audiolink, put audiolink-obs.dll in your obs plugins folder. usually: C:\Program Files\obs-studio\obs-plugins\64bit on windows

Once both are installed, open the audio link tool window in obs with "tools->audiolink" in the top bar.
Then select the audio source. this can be any source that handles audio in your scenes. hit refresh if it doesn't pop up.
Then make sure you have at least one obs-shader-filter filter attached to a source of video in one of your scenes
Now your custom filter shaders will automatically grab the following properties:
bass, lows, mids, treb
bass_c, lows_c, mids_c, treb_c
l_bass, l_lows, l_mids, l_treb
l_bass_c, l_lows_c, l_mids_c, l_treb_c
r_bass, r_lows, r_mids, r_treb
r_bass_c, r_lows_c, r_mids_c, r_treb_c
all these variables are floats you can use in your shader code and will automatically read from the audio bands
the prefix "l_" means its from the left stereo channel
the prefix "r_" means its only the right stereo channel
the suffix "_c" means the value is cumulative. As sounds play in a certain audio-band, cumulative values will increase til they hit one, then jump back to zero. These are useful for rotational effects or velocity effects in your shaders.

