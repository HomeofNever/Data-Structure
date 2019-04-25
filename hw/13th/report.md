
# Report 

## Author

Xinhao Luo, luox6@rpi.edu

## Basic Info

- XPS15 i7 8 Gen
- All time in sec
- Mode
    - random string
    - String Length: 2
- Test Script (Basic)
    - 5th test string numbers are based on different order notations

```bash
STRUCTURES=(vector list bst hash_table priority_queue)
OPERATIONS=(sort remove_dups_same_order remove_dups_any_order mode)
LENGTHS=(10000 20000 100000 500000)
LENGTH=2
EXEC=./cmake-build-debug/13th
OUTFILE=out.txt

for  S  in  ${STRUCTURES[@]};  do
	for  O  in  ${OPERATIONS[@]};  do
		for  L  in  ${LENGTHS[@]};  do
			${EXEC}  ${S}  ${O} random ${L}  ${LENGTH}  ${OUTFILE}
		done
	done
done
```
## Tests

### Vector

#### Sort

|# of Strings|Load Time|Operation Time|Output Time|
|---|---|---|---|
|10000|0|0.015625|0.0625|
|20000|0|0|0.125|
|100000|0.015625|0.046875|0.5|
|500000|0.046875|0.21875|2.75|
|1000000|0.09375|0.5|5.51562|

#### Remove_dups_same_order

|# of Strings|Load Time|Operation Time|Output Time|
|---|---|---|---|
|10000|0|0.046875|0.015625|
|20000|0|0.09375|0.015625|
|100000|0.015625|0.515625|0|
|500000|0.046875|2.67188|0|
|1000000|0.09375|5.21875|0.015625|


#### Remove_dups_any_order

|# of Strings|Load Time|Operation Time|Output Time|
|---|---|---|---|
|10000|0|0|0.015625|
|20000|0|0|0.015625|
|100000|0.015625|0.046875|0|
|500000|0.046875|0.234375|0.015625|
|5000000|1.28125|6.92188|0.09375|

#### Mode

|# of Strings|Load Time|Operation Time|Output Time|
|---|---|---|---|
|10000|0|0|0|
|20000|0|0.015625|0|
|100000|0|0.046875|0|
|500000|0.046875|0.234375|0|
|4000000|1|5.35938|0.09375|

### List

#### Sort

|# of Strings|Load Time|Operation Time|Output Time|
|---|---|---|---|
|10000|0|0|0.0625|
|20000|0|0.03125|0.125|
|100000|0|0.125|0.609375|
|500000|0.046875|0.671875|2.5|
|1000000|0.09375|1.59375|5.125|

#### Remove_dups_same_order

|# of Strings|Load Time|Operation Time|Output Time|
|---|---|---|---|
|10000|0.015625|0.09375|0.015625|
|20000|0.015625|0.203125|0.015625|
|100000|0|1.10938|0.015625|
|500000|0.046875|5.76562|0.046875|
|1000000|0.09375|11.9531|0.171875|


#### Remove_dups_any_order

|# of Strings|Load Time|Operation Time|Output Time|
|---|---|---|---|
|10000|0.015625|0|0|
|20000|0.015625|0.015625|0|
|100000|0.015625|0.09375|0.015625|
|500000|0.0625|0.671875|0.078125|
|3000000|0.453125|4.39062|0.4375|

#### Mode

|# of Strings|Load Time|Operation Time|Output Time|
|---|---|---|---|
|10000|0|0.015625|0|
|20000|0|0.03125|0|
|100000|0.10.125|0.05|
|500000|0.046875|0.8125|0.078125|
|1000000|0.109375|6.901625|0.609371|

### BST

#### Sort

|# of Strings|Load Time|Operation Time|Output Time|
|---|---|---|---|
|10000|0|0|0.0625|
|20000|0|0|0.109375|
|100000|0.015625|0.03125|0.515625|
|500000|0.046875|0.1875|2.78125|
|1000000|0.125|0.40625|5.07812|

#### Remove_dups_same_order

|# of Strings|Load Time|Operation Time|Output Time|
|---|---|---|---|
|10000|0|0|0.015625|
|20000|0.015625|0|0|
|100000|0.015625|0.03125|0|
|500000|0.0625|0.1875|0|
|20000000|0.6109375|7.403593|0.2187015|


#### Remove_dups_any_order

|# of Strings|Load Time|Operation Time|Output Time|
|---|---|---|---|
|10000|0|0|0|
|20000|0|0.015625|0|
|100000|0|0.046875|0|
|500000|0.046875|0.1875|0|
|2000000|1.85938|7.29688|0.2031|

#### Mode

|# of Strings|Load Time|Operation Time|Output Time|
|---|---|---|---|
|10000|0.015625|0|0|
|20000|0|0|0|
|100000|0.015625|0.03125|0|
|500000|0.046875|0.75|0.078125|
|3000000|0.296875|5.25|0.5|

### HashTable

#### Sort

N/A

#### Remove_dups_same_order

|# of Strings|Load Time|Operation Time|Output Time|
|---|---|---|---|
|10000|0|0|0|
|20000|0|0.015625|0|
|100000|0|0.03125|0.015625|
|500000|0.046875|0.15625|0.015625|
|15000000|1.375|4.17188|0.171875|


#### Remove_dups_any_order

|# of Strings|Load Time|Operation Time|Output Time|
|---|---|---|---|
|10000|0|0|0|
|20000|0.015625|0|0.015625|
|100000|0.015625|0.03125|0|
|500000|0.046875|0.15625|0.015625|
|15000000|1.45312|4.34375|0.15625|

#### Mode

|# of Strings|Load Time|Operation Time|Output Time|
|---|---|---|---|
|10000|0|0.015625|0|
|20000|0|0.015625|0|
|100000|0|0.03125|0|
|500000|0.046875|0.140625|0|
|20000000|2.0625|6.03125|0.21875|

### Priority Queue

#### Sort

|# of Strings|Load Time|Operation Time|Output Time|
|---|---|---|---|
|10000|0|0|0.0625|
|20000|0|0.015625|0.125|
|100000|0|0.109375|0.53125|
|500000|0.046875|0.640625|2.67188|
|1000000|0.09375|1.32812|5.125|

#### Remove_dups_same_order

N/A

#### Remove_dups_any_order

|# of Strings|Load Time|Operation Time|Output Time|
|---|---|---|---|
|10000|0|0.015625|0|
|20000|0|0.015625|0|
|100000|0.015625|0.109375|0|
|500000|0.046875|0.640625|0.015625|
|3000000|0.328125|4.95312|0.046875|

#### Mode

|# of Strings|Load Time|Operation Time|Output Time|
|---|---|---|---|
|10000|0|0.015625|0|
|20000|0.015625|0.015625|0|
|100000|0.015625|0.109375|0|
|500000|0.046875|0.640625|0|
|3000000|0.296875|4.65625|0.03625|

