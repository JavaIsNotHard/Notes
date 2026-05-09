fixes the flaws of tuple oriented approach

assumes that we can only append blocks instead of overwriting existing blocks

this makes writes faster because we dont' have to search for free space and go through various indirection layer but the disadvantage is that our reads are slower

