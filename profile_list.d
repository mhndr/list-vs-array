
dtrace:::BEGIN
{
    printf("Starting to measure List Insert function runtime...\n");
    self->start = 0;
    @total_time = sum(0);
    @count = count();
}

ListInsert$target:::entry
{
    /*print(arg0);*/
    self->start = timestamp;
}

ListInsert$target:::exit
/self->start != 0/
{
    @avgt= avg(timestamp - self->start);
    @count = count();
    self->start = 0;
}

dtrace:::END
{
    printa("Total executions: %-@8d\n", @count);
/*    normalize(@avgt, 1000); */
    printa("Average time per execution (ns):  %-@8d\n", @avgt);
}


