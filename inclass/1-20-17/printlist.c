int printlist(char *name, NODE *p)
{
	printf("%s - ", name);
	while(p)
	{
		printf("[%s %d] ->", p->name, p->ip);
		p = p->next;
	}
	printf("NULL\n");
}
