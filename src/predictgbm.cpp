#include <iostream>
#include <LightGBM/application.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <unistd.h>
#include <sys/time.h>
int main() {
  	char * model_filename = "LightGBM_model.txt";
	char * config_filename = "predict.conf";
	LightGBM::Application app(model_filename, config_filename);
	app.InitPredictOnline();
	std::vector<std::string> vector_data;
	vector_data.push_back(std::string("1	0.109	1.261	-0.274	2.605	0.472	-0.429	-0.983	1.000	-0.095	-1.219	-0.369	-0.312	-0.840	1.281	-0.618	-0.532	-0.132	0.443	0.028	2.201	0.044	1.671	0.660	-0.114	0.574	0.276	0.680	-0.670"));
	vector_data.push_back(std::string("4	-0.294	-0.659	-0.569	2.351	0.775	-0.339	-2.436	-1.704	0.086	-0.291	-1.152	-0.132	-0.745	-0.641	-0.173	-1.016	-1.386	-1.354	-0.405	-1.583	2.190	0.933	0.720	-0.885	-0.848	-1.416	1.838	1.343"));
	vector_data.push_back(std::string("2	0.194	1.849	-1.486	0.190	0.331	-1.080	-2.175	1.073	0.371	-1.200	0.022	0.784	-1.400	-0.130	-1.631	-0.166	0.156	0.944	0.360	-0.081	-0.736	0.534	-1.664	0.267	-0.813	0.871	0.924	-0.935"));
	vector_data.push_back(std::string("0	0.261	-0.391	-0.138	-0.822	0.774	-0.146	-0.738	-0.121	1.735	0.335	1.076	-1.612	-0.197	-1.000	-0.519	-0.767	1.289	0.717	-0.755	-0.465	0.363	0.891	1.041	0.635	1.814	0.427	-0.445	-0.815"));
	vector_data.push_back(std::string("2	0.547	-0.093	-0.077	-2.957	-0.713	0.933	0.970	-0.735	0.165	-0.189	0.690	2.209	0.708	-0.670	-0.078	1.402	-1.409	-0.615	0.710	1.294	0.609	-0.607	0.537	0.414	0.351	-0.097	0.053	-0.907"));
	vector_data.push_back(std::string("4	-0.544	1.656	0.213	2.566	-1.318	-0.301	-0.304	-0.777	-0.351	-0.480	-0.979	1.795	-0.083	0.927	0.990	1.428	-0.982	1.266	-0.074	2.036	0.525	-1.153	1.258	1.159	-1.292	0.745	1.604	0.479"));
	vector_data.push_back(std::string("2	0.499	0.546	-0.268	0.686	-0.923	-2.454	0.707	0.166	-0.610	-1.471	-2.037	0.052	1.649	-0.139	-0.361	-0.024	2.179	0.752	-0.934	0.028	0.332	-1.056	0.759	-0.818	-1.511	0.076	-0.082	-0.001"));
	vector_data.push_back(std::string("0	-0.651	-0.487	-0.592	-0.864	0.049	-0.831	0.270	-0.050	-0.239	-0.908	-0.577	0.755	0.501	-0.978	0.099	0.751	-1.669	0.543	-0.663	0.571	-0.763	-1.805	-1.628	0.048	0.260	-0.904	0.639	-1.662"));
	vector_data.push_back(std::string("4	-1.463	0.326	1.539	0.616	0.623	-0.292	1.767	0.728	0.818	0.100	0.842	-0.257	1.059	0.309	-0.462	1.705	-0.238	-0.841	2.439	0.076	-0.003	0.519	0.449	-0.589	-2.275	1.666	-0.145	1.938"));
	vector_data.push_back(std::string("2	0.837	0.724	-0.514	0.910	-1.161	1.077	-0.261	1.684	-1.521	1.763	-0.361	-0.379	0.195	-0.697	-0.072	-0.738	-0.701	0.487	-0.902	-0.768	-1.373	-0.504	1.312	-0.846	-0.732	0.194	-0.371	2.228"));
	for(int i =0;i<0;i++)
	{
		int size_=vector_data.size();
		for(int j=0;j<size_;j++)
		{
			vector_data.push_back(vector_data[j]);
		}
	}
	//the size should be 2^20=1048576
	printf("size:%d\n",vector_data.size());
	std::map<int, std::vector<double> >  result;
	timeval start_timestamp;
	gettimeofday(&start_timestamp,NULL);
	app.PredictOnline(vector_data, 0, result);
	timeval end_timestamp;
	gettimeofday(&end_timestamp,NULL);
	printf("%ld\n",start_timestamp.tv_sec);
	printf("%ld\n",end_timestamp.tv_sec);
	for(int k=0;k<result.size();k++)
	{
		for (int j = 0; j < result[k].size(); j++)
		{
			printf("%lf\t", result[k][j]);
		}
		printf("\n");
	}
	printf("Time elasped:%lf s\n",(end_timestamp.tv_sec-start_timestamp.tv_sec)+(end_timestamp.tv_usec-start_timestamp.tv_usec)/100000.0);
	//the time used is about 21.5 s.
	return 0;
}
