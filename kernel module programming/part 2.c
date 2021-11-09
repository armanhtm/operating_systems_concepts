#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>


static LIST_HEAD(birthday_list);
struct birthday {
		int day;
		int month;
		int year;
		struct list_head list;
	};

int add_birth(void){
	struct birthday *person = NULL;
	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->day = 2;
	person->month = 8;
	person->year = 1995;
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);


	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->day = 21;
	person->month = 6;
	person->year = 1998;
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);

	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->day = 2;
	person->month = 6;
	person->year = 1994;
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);

	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->day = 13;
	person->month = 1;
	person->year = 2000;
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);

	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->day = 30;
	person->month = 12;
	person->year = 2014;
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);


	struct birthday *ptr;
	list_for_each_entry(ptr, &birthday_list, list) {
	/*on each iteration ptr points to the next birthday struct*/

		printk(KERN_INFO "DATA:	%2d/%2d/%4d\n", ptr->day, ptr->month, ptr->year);
	}


	return 0;
}
void free_memory(void){
	struct birthday *ptr,*next;
	int i = 0;
	list_for_each_entry_safe(ptr, next, &birthday_list, list){
		list_del(&ptr->list);
		kfree(ptr);
		printk(KERN_INFO "person %d was deleted\n",i);
		i++;
	}
}




/* this function is called when the module is loaded*/
int simple_init(void)
{
	printk(KERN_INFO "Loading Module\n");
	add_birth();
	return 0;
}




/* this function is called when the module is removed*/
void simple_exit(void)
{
	free_memory();
	printk(KERN_INFO "Removing Module\n");
}



/* Macros for registering module entry and exit points.
*/
module_init(simple_init);
module_exit(simple_exit);



MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("simple module");
MODULE_AUTHOR("SGG");
