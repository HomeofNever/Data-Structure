
## Environment Overview

|Key|Value|
|---:|:---|
|Language Standard | C++ 11|
|Compiler | g++ (Debian 6.3.0-18+deb9u1) 6.3.0 20170516|
|gdb | GNU gdb (Debian 7.12-6) 7.12.0.20161007-git|
|Valgrind | 3.14.0|
|IDE|CLion 2018.3.3 Build #CL-183.5153.40, built on January 9, 2019|
|OS|Windows 10 Education 1803 17134.523|

## Bugs

### `--arithmetic-operations`

first, I tried running directly and catch the error message.

#### Issue 1

```
int uzlaki(): Assertion `qaut(wbijf,gqrre,ymvu,5,gqrre) == 5' failed.
```

##### Possible reasons

First, I chose to look into method `gaut`: 

```
float wlid = ((((hhyo / qykrae) / vuwpz) / rtazkk) / tval);
```

The result of integer division used in a floating point context may cause possible loss of precision. 

* Casting float `(float)` add the front of each variable.

However, the number given cannot reproduce such result, so I set a breakpoint in `gdb` and following result has shown:

![enter image description here](https://i.loli.net/2019/02/12/5c6245cd0a6c9.png)

It looked like the result did not match with the annotation.

```
int ukts_v = bfnfk_ - 3*xleony + 5*ymvu; //  32
```

* It should be `4 * ymvu`. Previously it is `36`

```
int agaal = (wbijf / ymvu) / xleony; //  3
```

* I added `+ ((wbijf / ymvu) % xleony > 0)` at the back since if we want  `100 / 4 / 10` (result 2.5) == 3, we need to do `ceil`

```
int ognpw = (wbijf / ukts_v) - agaal; // -1
```

I could not understand the purpose of line `(100 / 32) - 3` and it should be `0`.

* I did minus 1 manually.

```
int qidm = gqrre + dvyftr + ognpw + qangui; // -8
```

I could not know the purpose of this line `-1 + -2 + -1 + -3` 

* I did minus -1 manually.

```
float mzucv = xleony / wbijf; // 0.1
```

The result of integer division used in a floating point context may cause possible loss of precision.
* I cast int to float to avoid loss of precision. `(float) xleony`

### `--file-operations`

#### Issue when opening file

```bash
Usage: {PATH} operations infile outfile
Couldn't start operations.
```

##### Possible reasons

Method `teqd` handled file open. I searched error string for code location.

```cpp
// Error checking on command line arguments  
if(argc == 4) {  
  std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;  
  std::cerr << "Couldn't start operations." << std::endl;  
  return false;  
}
```

* `argc` should be 4, change `if` condition to `!=`

#### Issue when opening file 2

```
That file could not be opened!
```

##### Possible reasons

Again, I searched error string.

```
std::ifstream qqioi(argv[2], std::ifstream::binary);  
  
// make sure it's been opened correctly  
if(qqioi) {  
  std::cerr << "That file could not be opened!" << std::endl;  
  return false;  
}  
```

* `if` is about to check file is opened or not, condition should be `!qqioi.is_open()`

#### Issue when doing operation

```
bool teqd(int, char**, char*&, int&): Assertion `qqioi.gcount() != nciy' failed.
```

##### Possible reasons

Assertion tried to check data length. 

```
assert(qqioi.gcount() != nciy);
```

* the assertion condition should be `==` since `nciy` is the length of the data read in.

### `--array-operations`

#### Issue 1

```bash
Process finished with exit code -1
```

No explicit error message appeared.

##### Procedures

I tried finding where `array-operations` called in `main`:

```
if(ops == "--array-operations" || ops == "--all-operations") {  
  records[1] = xujz();  ...
}
```

I traced function `xujz()`, and set breakpoint at `line 653`, and SIGSEGV (Segmentation fault) caught at `line 650`.

After inspecting the first for-loop, I consider that:

`xsdus[yphmro+1]` will point to `NULL` since it is not init at the first for-loop.

* Since it did not make sense to `+1` in this for-loop (will be out of bound), I removed them;

* And if created an array with `[num]`, the range should be `0-24`; the later function uses the index directly `new` and this function is about to store a pair of coordinate, guess that `neug` should have the same index as `xsdus`: I have changed index accordingly.

However, the program still returned `-1`. I set a breakpoint at `line 666` found Segmentation fault at `line 657`.

```
assert(xsdus[-1][-1] == 0);
```

* Index `-1` did not make sense. Since it is testing the corner cases, I change them into `ohmgu - 1`


#### Issue when store number

I re-run the program after fixation

```
int xujz(): Assertion `xsdus[1][2] == -1' failed.
```

##### Procedures

I set up a breakpoint right after the loop and examine the expression `xsdus[1][2]`, which return `0`

* The breakpoint was skipped, it is found that the for-loop condition is wrong: I changed from `>=` to `<=`

I stepped into the source of the result provided (function ` ofxtfp`)

There are several Issues in this method:

 * The if condition should not be assignment, change accrodingly 
 * Only two conditions considered (missing`ribzwv` is hypotenuse)
 * Return `-1` when no found was not considered.

#### printing Issue

The padding when printing is not correct.

![DS_array](media/15499529075056/DS_array.png)

#####Procedures

I looked into where `std::cout` used:

* `((gldg < 10) ? " " : "")` missing a condition when int is `-1`:
add condition `&& gldg >= 0`

### `--vector-operations`

#### Issue 1

```
Process finished with exit code -1
```

No explicit error message

#####Procedures

I found method call in main:

```cpp
records[2] = taysxt();
```

I traced into this method and randomly set a breakpoint within the function (`line 147`); and nothing was breaking.

I stepped over; a Segmentation Fault found at `line 393` in method `wwqub`. From the note, it says it would modify the vector pass in.

* I changed parameters from copy into reference so the modification can be used later.

The index cannot be equal to the size of the vector

* I use `<` instead of `<=` in for-loop.

Since for-loop will access element at `i` and `i - 1`

* the initial condition should be 1 instead of 0.


* The return condition should be `size() -1`

#### Issue when doing sum on vector

```bash
int taysxt(): Assertion `hxzpt == 55' failed.
```

I set a breakpoint, found that vector `jahtu` sum is 45 rather than 55.

```cpp
// create another vector with entries 1-10  
std::vector<int> jahtu;  
for(uint idirjf=0; idirjf<10; ++idirjf) {  
  jahtu.push_back(idirjf);  
}
```

* I change initial condition from 0 to 1, and limitation `<=10`.

#### Issue 2
```
int taysxt(): Assertion `u_qg == 4' failed.
```

I set a breakpoint at `line 166`, and `u_qg` is a strange number: it is not initialize before increment.

* I initialize `u_gg` as 0 before using it.

#### Issue 3

```
int taysxt(): Assertion `clnx(frubrn, emtc)' failed.
```

#####Procedures

I trace into method `clnx`, it is used to compare two vector (`kfkzrc[size] > honidy[size]`).

However, the if condition set flag `uuuo` to `false` when condition matched: solve by reversing (`>` => `<=`) the comparision.  

#### Issue 4

```
Now counting numbers divisible by 3
```

The program seemed stuck here (running after a while without any output).

#####Procedures

I searched the string printed and found that the message printed at `line 222`. A for-loop is right after it.

```
for(uint fqfkg = 0; fqfkg < gqszp.size(); fqfkg+1) {
```

* The plus-one (`fqfkg + 1`) result not used: I changed it into `fqfkg+=1`

#### Issue 5

Segmentation Fault (Exit -1)

#####Procedures

I set a breakpoint randomly in the function and `line 235` appears a Segmentation Fault.

From the debugger variable dump, it is notice that the vector it loop through has only 12 elements while counter `u_qg` is 17

* I reset counter to 0 before increment.

Run again, problem still appears. Step by step going through the loop, found that `migm` go to a large int after 0, which cause the for-loop continue after minus

* I changed `unsigned int` to `int`.

#### Issue 6
```
Vector bugs are NOT FIXED
```

#####Procedures

The expected output does not matched. Re-visit the vector collected.

```
for(uint fqfkg = 0; fqfkg < gqszp.size(); fqfkg+=1) {  
    if(fqfkg % 3 == 0) {  
        // std::cout << gqszp[fqfkg] << " is divisible by 3" << std::endl;  
  u_qg++;  
  xdhiq.push_back(fqfkg);  
  }  
}
```

`fqfkg` is the counter and should not be pushed into vector, based on the comment given

* I changed `push_back(...)` into `gqszp[fqfkg]`

### `--list-operations`

#### Issue 1
Run the program for the first time:

```
Assertion `fkciz.back() == 'z'' failed.
```

#####Procedures

The for-loop seemed to have some Issue:

```
char pqic = 'a'; pqic >= 'z'; pqic++
```

* Letter `z` should be larger than `a`, changed condition accordingly.

#### Issue 2

Found Segmentation Fault at `line 283`

#####Procedures

I doubted that Segmentation Fault should be a kind of out-of-bound issue, so I check the for-loop:

```
for(std::list<int>::iterator swem = nvlahj.begin(); swem != nvlahj.end(); ++swem) {  
  if(*swem % zsclz != 0 || *swem % loies != 0) {  
    nvlahj.erase(swem);  
  }  
}
```

* `erase` will return the next element and should be used to replace current iterator.

#### Issue 3

```
elderberry ...
-1224707885 letters did not ever appear in the fruit names.
int zbna(): Assertion `*fkciz.begin() == 'A'' failed.
```

#####Procedures

* The int printed looks strange, it is not initialized.

I compared my output with `expected_output.txt`, the fruit list is not complete.

```
// remove non-fruits from the list
...
bijqwy.erase(++bkrm);
```

* `erase` should remove target rather than `++target`

I used GDB and set a breakpoint at `line 361`, print out what is inside `fkciz`. It is noticed that the list start with `Z`. The order of the list is wrong when initialize.

* I reversed the for-loop for upper-case letter first and then lower-case letter.
* I replaced `push_front` with `push_back`.

## Memory Leaks

#### `--array-operations`

the `neug` needed to be manually deleted.

#### `--file-operations`

the `char*` was used for decryption, and need to be deleted at the end of `int main()`.


