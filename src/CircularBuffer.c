<CB ​ ​ enum ​ ​ type> ​ ​ CB_buffer_add_item(<buffer ​ ​ to ​ ​ add ​ ​ to>, ​ ​ <data ​ ​ to ​ ​ add>);
1. The ​ ​ function ​ ​ will ​ ​ take ​ ​ 2 ​ ​ arguments:
a. Pointer ​ ​ to ​ ​ the ​ ​ circular ​ ​ buffer ​ ​ to ​ ​ which ​ ​ the ​ ​ data ​ ​ item ​ ​ is ​ ​ to ​ ​ be ​ ​ added
b. The ​ ​ data ​ ​ to ​ ​ be ​ ​ added ​ ​ to ​ ​ the ​ ​ circular ​ ​ buffer
2. ​ ​ The ​ ​ function ​ ​ returns ​ ​ an ​ ​ enumeration ​ ​ that ​ ​ specifies ​ ​ the ​ ​ success, ​ ​ failure ​ ​ etc. ​ ​ of ​ ​ the ​ ​ function ​ ​ call
3. Must ​ ​ take ​ ​ into ​ ​ consideration ​ ​ the ​ ​ corner ​ ​ cases ​ ​ possible
<CB ​ ​ enum ​ ​ type> ​ ​ CB_buffer_remove_item(<buffer ​ ​ to ​ ​ remove ​ ​ from>, ​ ​ <variable ​ ​ to ​ ​ store ​ ​ data ​ ​ removed>);
1. The ​ ​ function ​ ​ will ​ ​ take ​ ​ 2 ​ ​ arguments:
a. Pointer ​ ​ to ​ ​ the ​ ​ circular ​ ​ buffer ​ ​ from ​ ​ which ​ ​ the ​ ​ data ​ ​ item ​ ​ is ​ ​ to ​ ​ be ​ ​ removed
b. Variable ​ ​ to ​ ​ store ​ ​ and ​ ​ return ​ ​ the ​ ​ removed ​ ​ item ​ ​ from ​ ​ the ​ ​ buffer
2. The ​ ​ function ​ ​ returns ​ ​ an ​ ​ enumeration ​ ​ that ​ ​ specifies ​ ​ the ​ ​ success, ​ ​ failure ​ ​ etc. ​ ​ of ​ ​ the ​ ​ function ​ ​ call
3. Must ​ ​ take ​ ​ into ​ ​ consideration ​ ​ the ​ ​ corner ​ ​ cases ​ ​ possible
<CB ​ ​ enum ​ ​ type> ​ ​ CB_is_full(<buffer ​ ​ to ​ ​ check>);
1. The ​ ​ function ​ ​ will ​ ​ take ​ ​ in ​ ​ the ​ ​ circular ​ ​ buffer ​ ​ to ​ ​ check ​ ​ if ​ ​ it ​ ​ is ​ ​ full
2. The ​ ​ function ​ ​ returns ​ ​ the ​ ​ status ​ ​ of ​ ​ the ​ ​ circular ​ ​ buffer ​ ​ or ​ ​ an ​ ​ error ​ ​ code
<CB ​ ​ enum ​ ​ type> ​ ​ CB_is_empty(<buffer ​ ​ to ​ ​ check>);
1. The ​ ​ function ​ ​ will ​ ​ take ​ ​ in ​ ​ the ​ ​ circular ​ ​ buffer ​ ​ to ​ ​ check ​ ​ if ​ ​ it ​ ​ is ​ ​ empty
2. The ​ ​ function ​ ​ returns ​ ​ the ​ ​ status ​ ​ of ​ ​ the ​ ​ circular ​ ​ buffer ​ ​ or ​ ​ an ​ ​ error ​ ​ codes
<CB ​ ​ enum ​ ​ type> ​ ​ CB_peek(<buffer ​ ​ to ​ ​ peek ​ ​ into>, ​ ​ <position ​ ​ to ​ ​ peek>);
1. The ​ ​ function ​ ​ will ​ ​ take ​ ​ 2 ​ ​ arguments:
a. Pointer ​ ​ to ​ ​ the ​ ​ circular ​ ​ buffer ​ ​ to ​ ​ peek ​ ​ into
b. The ​ ​ position ​ ​ from ​ ​ the ​ ​ head ​ ​ of ​ ​ the ​ ​ buffer ​ ​ to ​ ​ peek ​ ​ into
2. The ​ ​ function ​ ​ returns ​ ​ the ​ ​ status ​ ​ of ​ ​ the ​ ​ circular ​ ​ buffer ​ ​ or ​ ​ an ​ ​ error ​ ​ code
3. Must ​ ​ take ​ ​ into ​ ​ consideration ​ ​ the ​ ​ corner ​ ​ cases ​ ​ possible
<CB ​ ​ enum ​ ​ type> ​ ​ CB_init(<pointer ​ ​ of ​ ​ buffer ​ ​ type>, ​ ​ <length ​ ​ of ​ ​ buffer>);
1. The ​ ​ function ​ ​ will ​ ​ take ​ ​ 2 ​ ​ arguments:
a. Pointer ​ ​ to ​ ​ the ​ ​ circular ​ ​ buffer
b. The ​ ​ length/size ​ ​ to ​ ​ be ​ ​ reserved ​ ​ for ​ ​ the ​ ​ buffer
2. The ​ ​ function ​ ​ returns ​ ​ the ​ ​ status ​ ​ of ​ ​ the ​ ​ circular ​ ​ buffer ​ ​ or ​ ​ an ​ ​ error ​ ​ codes
<CB ​ ​ enum ​ ​ type> ​ ​ CB_destroy(<pointer ​ ​ of ​ ​ buffer ​ ​ type>);
1. The ​ ​ functions ​ ​ takes ​ ​ in ​ ​ the ​ ​ buffer ​ ​ to ​ ​ be ​ ​ destroyed
2. The ​ ​ function ​ ​ returns ​ ​ the ​ ​ status ​ ​ of ​ ​ the ​ ​ circular ​ ​ buffer ​ ​ or ​ ​ an ​ ​ error ​ ​ codes
