# luxoft_upskill_ex01

## build

<p>build the main test with</p>
<pre><code>make build</code></pre>

<p>build the single threaded test with</p>
<pre><code>make build_test01</code></pre>

## run

<p>run the main test with</p>
<pre><code>./main</code></pre>

<p>run the single threaded test with</p>
<pre><code>./test01</code></pre>

## requirments

Implement a single-linked API (add, delete, print_list, sort_list): 
- add_node - adds a new node to the end of list, each value has to be unique
- delete_node - deletes the specified element
- print_list - prints the nodes of the list(each element of the list has a member callback_print which stores the function executed to show the node informations)
- sort_list - rearrange the list from the lower to the higher value of the nodes
- flush_list  - reset the list (delete all the nodes)


3 threads will be created and will do some work on the list :
 
Thread1:
- add(2)
- add(4)
- add(10)
- delete(2)
- sort_list()
- delete(10)
- delete(5)
                        
Thread2: 
- add(11)
- add(1)
- delete(11)
- add(8)
- print_list()
                        
Thread3:
- add(30)
- add(25)
- add(100)
- sort_list()
- print_list()
- delete(100)

NODE informations:
The node should have the following members beside next pointer:
- callback for the print function to be used when displaying the element
- val -> the value of the element added

Observations:
- Use a synchronisation method to wait until all threads are created before starting executing threads instructions.
- When executing the program print the action executed (add, delete, print, etc) by each thread and the thread id which executes it.
- Before flushing the list at the end of the program display the list in the final state after threads actions.
