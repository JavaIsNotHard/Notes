```
import { useState } from 'react';

export default function Counter() {
  const [number, setNumber] = useState(0);

  return (
    <>
      <h1>{number}</h1>
      <button onClick={() => {
        setNumber(number + 1);
        setNumber(number + 1);
        setNumber(number + 1);
      }}>+3</button>
    </>
  )
}
```
in this example code, we might expect for each button click to increment the value of number by 3 each time, but it actually increments the value by 1. why??

in the initial render the value of the component's state will look like this
```
<button onClick={() => {
  setNumber(0 + 1);
  setNumber(0 + 1);
  setNumber(0 + 1);
}}>+3</button>
```

for the next render it looks like this
```
<button onClick={() => {
  setNumber(1 + 1);
  setNumber(1 + 1);
  setNumber(1 + 1);
}}>+3</button>
```

### State over time
```
import { useState } from 'react';

export default function Counter() {
  const [number, setNumber] = useState(0);

  return (
    <>
      <h1>{number}</h1>
      <button onClick={() => {
        setNumber(number + 5);
        setTimeout(() => {
          alert(number);
        }, 3000);
      }}>+5</button>
    </>
  )
}

```

**A state variable’s value never changes within a render,** even if its event handler’s code is asynchronous.
here in the above example, the initial state value of number is 0, which means the initial render has the value of 0, when we call setNumber(0 + 5), it triggers a render with state snapshot as 0, we also have a alert that executes asynchronously after 3 seconds, 
we might expect that since after 3 seconds the component already renders, it should alert with 5 for the first button click but it will return 0 instead. why?
because in the initial state snapshot the value of number was 0 and the state value number used by alert uses this number inside the setTimeout, which will result in a 0 value being alerted

## batching state updates

when we perform multiple state updates continuously or sequentially then those updates are batched to prevent multiple re-renders for each state update

Before React 18: only event handlers were batched

If you ever _want_ to force React to re-render immediately without waiting, React gives you an escape hatch called `flushSync`



## Updating objects in state

### copying objects with spread syntax



## Updating array in state

adding -> concat, `[...arr]`
deleting -> filter, slice
updating -> map


### Thinking about UI declaratively

1. identify your component's different visual states
2. determine what triggers those state changes
3. represent the state in memory using useState
4. remove any non-essential state variables
5. connect the event handlers to set the state

• It two state variables always update together, consider merging them into one.
• Choose your state variables carefully to avoid creating "impossible" states.
• Structure your state in a way that reduces the chances that you'll make a mistake updating it.
• Avoid redundant and duplicate state so that you don't need to keep it in sync.
• Don't put props into state unless you specifically want to prevent updates.
• For Ul patterns like selection, keep ID or index in state instead of the object itself.
• If updating deeply nested state is complicated, try flattening it.


