#include <iostream>
#include <LightGBM/application.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char** argv) {
	//printf("Hello This is a test...\n");
	//printf("Welcome!\n");
 // try {
 //   LightGBM::Application app(argc, argv);
 //   app.Run();
 // }
 // catch (const std::exception& ex) {
 //   std::cerr << "Met Exceptions:" << std::endl;
 //   std::cerr << ex.what() << std::endl;
 //   exit(-1);
 // }
 // catch (const std::string& ex) {
 //   std::cerr << "Met Exceptions:" << std::endl;
 //   std::cerr << ex << std::endl;
 //   exit(-1);
 // }
 // catch (...) {
 //   std::cerr << "Unknown Exceptions" << std::endl;
 //   exit(-1);
 // }
	char * model_filename = "LightGBM_model.txt";
	char * config_filename = "predict.conf";
	LightGBM::OnlineApp app(model_filename, config_filename);
	app.InitPredict();
	std::vector<std::string> vector_data;
	vector_data.push_back(std::string("1	0.109	1.261	-0.274	2.605	0.472	-0.429	-0.983	1.000	-0.095	-1.219	-0.369	-0.312	-0.840	1.281	-0.618	-0.532	-0.132	0.443	0.028	2.201	0.044	1.671	0.660	-0.114	0.574	0.276	0.680	-0.670"));
	vector_data.push_back(std::string("4	-0.294	-0.659	-0.569	2.351	0.775	-0.339	-2.436	-1.704	0.086	-0.291	-1.152	-0.132	-0.745	-0.641	-0.173	-1.016	-1.386	-1.354	-0.405	-1.583	2.190	0.933	0.720	-0.885	-0.848	-1.416	1.838	1.343"));
	vector_data.push_back(std::string("2	0.194	1.849	-1.486	0.190	0.331	-1.080	-2.175	1.073	0.371	-1.200	0.022	0.784	-1.400	-0.130	-1.631	-0.166	0.156	0.944	0.360	-0.081	-0.736	0.534	-1.664	0.267	-0.813	0.871	0.924	-0.935"));
	vector_data.push_back(std::string("0	0.261	-0.391	-0.138	-0.822	0.774	-0.146	-0.738	-0.121	1.735	0.335	1.076	-1.612	-0.197	-1.000	-0.519	-0.767	1.289	0.717	-0.755	-0.465	0.363	0.891	1.041	0.635	1.814	0.427	-0.445	-0.815"));
	vector_data.push_back(std::string("2	0.547	-0.093	-0.077	-2.957	-0.713	0.933	0.970	-0.735	0.165	-0.189	0.690	2.209	0.708	-0.670	-0.078	1.402	-1.409	-0.615	0.710	1.294	0.609	-0.607	0.537	0.414	0.351	-0.097	0.053	-0.907"));
	std::vector< std::vector<double> > result;
	app.Predict(vector_data, 0, result);
	for (int i = 0; i < result.size(); i++)
	{
		for (int j = 0; j < result[i].size(); j++)
		{
			printf("%llf\t", result[i][j]);
		}
		printf("\n");
	}

}
