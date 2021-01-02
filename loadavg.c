#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/livepatch.h>

/* Replacement code */
#include <linux/seq_file.h>
static int klp_loadavg_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "1.2 3.4 5.6 78/90 123\n");
	return 0;
}

/* Livepatch boilerplate */
static struct klp_func funcs[] = {
	{
		.old_name = "loadavg_proc_show",
		.new_func = klp_loadavg_proc_show,
	}, { }
};

static struct klp_object objs[] = {
	{
		.funcs = funcs,
	}, { }
};

static struct klp_patch patch = {
	.mod = THIS_MODULE,
	.objs = objs,
};

static int klp_loadavg_init(void)
{
	return klp_enable_patch(&patch);
}

static void klp_loadavg_exit(void)
{
}

module_init(klp_loadavg_init);
module_exit(klp_loadavg_exit);
MODULE_LICENSE("GPL");
MODULE_INFO(livepatch, "Y");
MODULE_DESCRIPTION("Livepatch test: loadavg");
