clock_t clk = clock();
    // code goes here
clk = clock() - clk;
cout << "Time Elapsed: " << fixed << setprecision(10) << ((long double)clk)/CLOCKS_PER_SEC << "\n";
