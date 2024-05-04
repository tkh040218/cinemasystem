#include<iostream>
#include<string>
#include<iomanip>

using namespace std;

class movie
{		
	string m_name,m_code;
	
	protected:
	
	double a_price;		
	int sit=40;
	int sitno[5][8] = {{1, 2, 3, 4, 5, 6, 7, 8},{9, 10, 11, 12, 13, 14, 15, 16},{17, 18, 19, 20, 21, 22, 23, 24},{25, 26, 27, 28, 29, 30, 31, 32},{33, 34, 35, 36, 37, 38, 39, 40}};	
	
	public:
		int counter ;
		movie():m_name(""),m_code(""),a_price(0.00),counter(1){}
		movie(string a ,string b,double c)
		{
			m_name  = a;
			m_code  = b;
			a_price = c;
		}
		movie(int i)//setting counter for remove movie
		{
			counter = i;	
		}
		double getadult()//accessor
		{
			return a_price;
		}
		string getmovie()//accessor
		{
			return m_name;
		}
		string getcode()//accessor
		{
			return m_code;
		}	
		int getsit()
		{
			return sit;	
		}
		void movieavaible()//display movie available
		{
			if( counter != 1 )
				{
					cout<<fixed<<setw(20)<<setprecision(2)<<m_name<<"\t\t"<<m_code<<"\t\t"<<a_price<<"\t\t\t";				
				}
		}
		void seatdisplay()//call seat display
		{
			cout<<"=============================================================================================================================\n";
			cout<<"  		      	        		      SCREEN  IS  HERE                    "<<endl;
			cout<<"-----------------------------------------------------------------------------------------------------------------------------\n";
			for(int i = 0 ; i < 5 ; i++)
			{
				cout<<"				";
				for(int j =0 ; j < 8 ; j++)
					if( sitno[i][j] < 0)
					{
						cout<<"|\\"<<setw(2)<<"=="<<"/|"<<"  ";
					}
					else
						cout<<"|\\"<<setw(2)<<sitno[i][j]<<"/|"<<"  ";
			
			cout<<"\n\n";		
			}
			cout<<"						  SEAT AVAILABLE : "<<sit<<endl;
									
		}		
};

class screen:public movie
{
	double price;
	int quantity = 0;
	string name,code;
	
	public:
		screen():price(0.00),quantity(0),name(""),code(""){}	
		
		void reset( movie &a)//function reset data of object for deleting
		{
			price = 0;
			quantity = 0 ;
			name  = "";
			code  = "";					
		}	
		
		void setdata( movie &a)//order and setdata
		{
			price = a.getadult();
			name  = a.getmovie();
			code  = a.getcode();					
		}
	
	friend class cart;
};

class seat:public movie//order and setdata
{
		
		int a,b,quantity;
		int arr[40];
		public:
		seat():quantity(0){}
		void setquantity(int &e)
		{
			quantity = e;
		}
		void select()//set order for seat
		{	
		int io;//counter for prevent repeat seat order
			cout<<"						  CHOOSE "<<quantity<<" SEATS : ";
			for( int k = 0 ; k < quantity ; k++)
			{
				
				do{	//to prevent repeat seat order 
					io = 1;
					cin>>arr[k];
					cout<<"                                                                   ";
					for(int i = 0 ; i < 5 ; i++)
					{		
						for(int j = 0 ; j < 8 ; j++)
							{
								if(  sitno [i][j] != arr[k]  )
								io++;
							}
						if(io>40)
						{	cout<<"\n                                         INVALID SEAT/SEAT OCCUPIED / REENTER .\n";
							cout<<"                                                                   ";
						}
					}
				}while( io > 40 );
				
				for(int i = 0; i <5 ; i++ )
				{
				for(int j = 0 ; j < 8 ;j++)
					if(  sitno[i][j] == arr[k] )
					{
						int a = 0;
						a = -1 * arr[k];
							sitno[i][j] = a ;
							sit--;
					}
				}
			}
			cout<<endl;
		}
		void edit(int &q)//undo order for seat
		{
			for(int i = 0 ; i < q ;i++)
			{
				int a = 0;
				a = arr[i];
				a = a * -1;
				for( int j = 0 ; j < 5; j++ )
					{
						for(int k = 0; k < 8 ;k++)
						{
							if( sitno[j][k] == a)
							{		sitno[j][k] = a *-1;
									sit++;
							}

						}				
					}		
			}	 
	    	    
		}				
	friend class cart;
};

class cart//display cart
{
	double total=0,price;
	string mname,mcode;
	int quantity ,arr[40];
	public:
		cart():total(0.00){}
		void cal(screen &B,seat &C)//sending class reference to screen and seat to cart function
		{
			total = B.price * C.quantity;
			
		}
		void setdata(screen &B,seat &C)
		{
			mname = B.name;
			mcode = B.code;
			price = B.price;
			quantity = C.quantity;
			for ( int i = 0 ; i < C.quantity ; i++ )
			{
				arr[i]= C.arr[i];
			}	
		}
		void display(screen &B,seat &C)
		{
			cout<<"			_________./	     ____    _    _____  _______ 	_________./					"<<endl;
			cout<<"			#########|	    / ___|  / \\  |  _  \\ |__  _|	#########|					"<<endl;
			cout<<"			 ########|	   | |     / _ \\ | |_) |   | | 		 ########|					"<<endl;
			cout<<"			 ________\\	   | |___ / ___ \\|  _ <    | |  	 ________\\					"<<endl;
			cout<<"			(o)    (o)	    \\____/_/   \\_|_| \\_\\   |_|	    	(o)    (o)					"<<endl;
			cout<<"\n";
			cout<<"============================================================================================================================="<<endl;
				cout<<"						   MOVIE       CODE        Price    Quantity    Total  "<<endl;
				if(	C.quantity != 0)
				{	
					cout<<"						"<<fixed<<setprecision(2)<<setw(10)<<B.name<<setw(10)<<B.code<<setw(12)<<B.price<<setw(9)<<C.quantity<<setw(12)<<total<<endl;
					cout<<"					           SEAT No : ";
				for(int i = 0 ; i < C.quantity; i++)
				{
					cout<<C.arr[i]<<" ";
				}
				}
				cout<<"\n\n";
		}	
		void receipt(screen &B,seat &C)
		{
			if(C.quantity<4)
			{
				cout<<"		 ___________________   _____________________________________	"<<endl;
				cout<<"		|___________________\\/______________________________________|	"<<endl;
				cout<<"		|  MOVIE TICKET	    ::MOVIE:	"<< B.name <<"		    |	"<<endl;
				cout<<"		|___________________::______________________________________|	"<<endl;
				cout<<"		|		    ::THEATER:	" << B.code <<"			    |	"<<endl;
				cout<<"		|		    ::PRICE:	" << B.price <<"			    |	"<<endl;
				cout<<"		|		    ::QUANTITY:	" << C.quantity <<" 			    |	"<<endl;
				cout<<"		|		    ::SEAT NO. :";for (int i = 0; i < C.quantity; i++)
														{
											   				 cout << C.arr[i]<<" ";
														}
				cout<<										"			    |"<<endl;
				
				
				
				
				cout<<"		|		    ::					    |	"<<endl;
				cout<<"		|		    ::					    |	"<<endl;
				cout<< fixed << setprecision(2) << "		|		    ::			TOTAL : RM" << total << "	    |	"<<endl;
				cout<<"		\\___________________/\\_____________________________________/	"<<endl;
			}
			else if(C.quantity<8)
			{
				cout<<"		 ___________________   _____________________________________	"<<endl;
				cout<<"		|___________________\\/______________________________________|	"<<endl;
				cout<<"		|  MOVIE TICKET	    ::MOVIE:	"<< B.name <<"		    |	"<<endl;
				cout<<"		|___________________::______________________________________|	"<<endl;
				cout<<"		|		    ::THEATER:	" << B.code <<"			    |	"<<endl;
				cout<<"		|		    ::PRICE:	" << B.price <<"			    |	"<<endl;
				cout<<"		|		    ::QUANTITY:	" << C.quantity <<" 			    |	"<<endl;
				cout<<"		|		    ::SEAT NO. :";for (int i = 0; i < C.quantity; i++)
														{
											   				 cout << C.arr[i]<<" ";
														}
				cout<<										"		    |"<<endl;
				
				
				
				
				cout<<"		|		    ::					    |	"<<endl;
				cout<<"		|		    ::					    |	"<<endl;
				cout<< fixed << setprecision(2) << "		|		    ::			TOTAL : RM" << total <<"	    |"<<endl;
				cout<<"		\\___________________/\\_____________________________________/	"<<endl;
			}
			else 
				{
				cout<<"		 ___________________   _____________________________________	"<<endl;
				cout<<"		|___________________\\/______________________________________|	"<<endl;
				cout<<"		|  MOVIE TICKET	    ::MOVIE:	"<< B.name <<"		    |	"<<endl;
				cout<<"		|___________________::______________________________________|	"<<endl;
				cout<<"		|		    ::THEATER:	" << B.code <<"			    |	"<<endl;
				cout<<"		|		    ::PRICE:	" << B.price <<"			    |	"<<endl;
				cout<<"		|		    ::QUANTITY:	" << C.quantity <<" 			    |	"<<endl;
				cout<<"		|		    ::SEAT NO. :";for (int i = 0; i < C.quantity; i++)
														{
											   				 cout << C.arr[i]<<" ";
														}
				cout<<"	    |"<<endl;
				
				
				
				
				cout<<"		|		    ::					    |	"<<endl;
				cout<<"		|		    ::					    |	"<<endl;
				cout<< fixed << setprecision(2) << "		|		    ::			TOTAL : RM"<< total<<"    |"<<endl;
				cout<<"		\\___________________/\\_____________________________________/	"<<endl;
			}
			
			
			

		}
		
		friend class extra;
};

class extra//setup total
{
	string mname ,mcode;
	int quantity,arr[40];
	double price ,total;
	
	public:
		extra()
		{
			mname ="";
			mcode ="";
			quantity = 0;
			price = 0;
			total = 0;			
		}
		void reset()
		{
			quantity = 0 ;
			total =0;
		}
		void setdata(cart &D)
		{
			mname = D.mname;
			mcode = D.mcode;
			price = D.price;
			quantity = D.quantity;
			total = D.total;
			for( int i = 0 ; i <D.quantity ; i++)
			{
				arr[i]= D.arr[i];
			}		
		}
		void display()
		{
			if(quantity != 0)
			{	cout<<fixed<<setprecision(2)<<"           "<<mname<<"           "<<mcode<<"           "<<price<<"          "<<quantity<<"          "<<total<<"      ";
				for(int i = 0 ; i < quantity ; i++ )
				{
					cout<<arr[i]<<" ";
				}
				cout<<endl;
			}
		}
		double gettotal()
		{
			return total;
		}
};

void MenuDisplay()
{
	cout<<"						.-------------------------."<<endl;
	cout<<"						|   ____ ____ ____ ____   |"<<endl;
	cout<<"						|  ||M |||E |||N |||U ||  |"<<endl;
	cout<<"						|  ||__|||__|||__|||__||  |"<<endl;
	cout<<"						|  |/__\\|/__\\|/__\\|/__\\|  |"<<endl;
	cout<<"						|                         |"<<endl;
	cout<<"						| 1. Movie Available      |"<<endl;
	cout<<"						| 2. Order                |"<<endl;
	cout<<"						| 3. Edit Order           |"<<endl;
	cout<<"						| 4. Cart Display         |"<<endl;
	cout<<"						| 5. Seat Display Check   |"<<endl;
	cout<<"						| 6. Comfirm Order        |"<<endl;
	cout<<"						| 7. ETC.                 |"<<endl;
	cout<<"						| 0. Exit Program.        |"<<endl;
	cout<<"						'-------------------------'\n"<<endl;
}

void header()
{
	cout<<"			                _____________________________________________					"<<endl;
	cout<<"				      //:::::::::::::::::::::::::::::::::::::::::::::\\\\					"<<endl;
	cout<<"				    //:::_______:::::::::________::::::::::_____:::::::\\\\				"<<endl;
	cout<<"				  //:::_/   _-'':::_--'''        ''--_::::\\_  ):::::::::\\\\				"<<endl;
	cout<<"				 //:::/    /:::::_'                    '-_:::\\/:::::|^\\:::\\\\			"<<endl;			 
	cout<<"				//:::/   /~::::::I__                      \\:::::::::|  \\:::\\\\			"<<endl;
	cout<<"				\\:::\\   (::::::::::''''---___________     \\--------|  /::://			"<<endl;
	cout<<"				 \\:::\\  |:  ___ _____    __  __ ___  __   ____  __/ ::::://			"<<endl;
	cout<<"				  \\::::\\/  / __\\\\_   \\/\\ \\ \\/__/ _ \\/ /  /__\\ \\/ / :::://              "<<endl;
	cout<<"				    \\:::: / /    / /\\/  \\/ /_\\/ /_)/ /  /_\\  \\  / :::://				"<<endl;
	cout<<"				      \\:\\/ /__/\\/ /_/ /\\  //_/ ___/ /__//__  /  \\ ://					"<<endl;
	cout<<"				        \\\\____\\____/\\_\\ \\/\\__\\/   \\____\\__/ /_/\\_\\://					"<<endl;
	cout<<"				          \\::::\\    __----__                )::://						"<<endl;
	cout<<"				            \\:::\\/~::::::::~\\_         __/~:://						"<<endl;
	cout<<"				              \\::::::::::::::::''----'':::://							"<<endl;
	cout<<"				                \\::::::::::::::::::::::::://							"<<endl;
	cout<<"				                  \\:::\\^''--._.--''^/::://								"<<endl;
	cout<<"				                    \\:::\\         /::://								"<<endl;
	cout<<"				                      \\:::\\     /::://									"<<endl;
	cout<<"				                        \\:::\\_/::://									"<<endl;
	cout<<"				                          \\::::://										"<<endl;
	cout<<"				                            \\_//										"<<endl;
	cout<<"\n";
	cout<<"\n";
	cout<<"============================================================================================================================="<<endl;
	cout<<"\n";
	cout<<"                                                    WELCOME TO CINEPLEX"<<endl;
	cout<<"                                                      ORDERING SYSTEM";
	cout<<"\n";
}
int main()
{
	int def=3;//default movie on showing
	int choice,replace,quantity = 0,extracounter = 1;
	string add,code;
	double a_price,c_price,grand=0;
	
	movie *A = new movie[8]; //max 8 movie to added/on showing
	screen B;//ticket purchase for adult
	seat *C= new seat[8];//seat listing for each movie
	cart D;//display total 
	extra *E = new extra[10]; //adding new order 
	
	A[0]={"Spiderman","MX1001",14.00};//default movie detail
	A[1]={"Superman","MX1002",13.00};//default movie detail
	A[2]={"Aquaman","MX1003",12.00};//default movie detail
	header();
//main menu function:
	do{
		int set ,ac;//
		MenuDisplay();
		cout<<"						ENTER UR CHOICE : ";
		cin>>choice;
		cout<<endl;
		switch(choice)
		{
		case 1 ://display movie available 
					cout<<"			----------------------------------------------------------------------------------------"<<endl;
					cout<<"			|                                       NOW SHOWING                                     |"<<endl;
					cout<<"			----------------------------------------------------------------------------------------"<<endl;
					cout<<"			SELECT"<<"         MOVIE           "<<" M.CODE"<<"          PRICE               MAX.SEAT   "<<endl;
					for(int i = 0 ; i<def ; i++)
					{
						if(A[i].counter != 1)
							{
								cout<<"			"<<i+1;
								A[i].movieavaible();
								cout<<C[i].getsit()<<endl;;
							}
					}
					cout<<"			___________________________________________________________________________________________"<<endl;
					break;
		case 2 ://order 
					if( quantity > 0 )
					{	
						cout<<setw(65)<<"REPEAT ORDER ~ \n";
						break;
					}
					cout<<" 		 ---------------------------------------------------------------------------------------- "<<endl;
					cout<<"	 	 |                                       NOW SHOWING                                     |"<<endl;
					cout<<" 		 ---------------------------------------------------------------------------------------- "<<endl;
					cout<<"			SELECT"<<"         Movie           "<<" M.CODE"<<"          Price               Max.Seat   "<<endl;
					for(int i = 0 ; i<def ; i++)
					{
						if(A[i].counter != 1)
							{
								cout<<"			";
								cout<<i+1;
								A[i].movieavaible();
								cout<<C[i].getsit()<<endl;;
							}
					}
					cout<<"\n					Enter( 1 ~ 8 )SELECT to booking (0 . return MAIN ): ";
					cin>>set;
					if(set == 0 )
						     break;
					do
					{
						if(A[set-1].counter == 1 || set > 8 ||  set < 1)//for prevent access to array with counter=1
						{		
							cout<<"						INVALID INPUT! PLEASE RE-ENTER. ";
							cin>>set;
							cin.sync();							
						}
					}while(A[set-1].counter == 1 || set > 8 || set < 1 );	
						
					B.setdata(A[set-1]);
					cout<<"						  ENTER QUANTITY : ";
					cin>>quantity;
					C[set-1].setquantity(quantity);
				    cout<<"\n                                                   MOVIE :| "<<A[set-1].getmovie()<<"  |\n";		
					C[set-1].seatdisplay();
					C[set-1].select();
					D.cal(B,C[set-1]);							
			        break;
		case 3 ://edit order
					if( quantity == 0)
						{
							cout<<"						HAVEN'T ORDER YET. RETURN TO MAIN \n";
							break;
						}					
					cout<<"						1. EDIT QUANTITY AND SEAT "<<endl;
					cout<<"						2. DELETE ORDER           "<<endl;
					cout<<"						0. BACK MAIN.             "<<endl;
					int pick;
					do{
					cout<<"						";
					cin>>pick;
					switch(pick)
					{
						case 1:	
								cout<<"\n                                                   MOVIE :| "<<A[set-1].getmovie()<<"  |\n";	
								C[set-1].edit(quantity);
								C[set-1].seatdisplay();
								cout<<"						  ENTER QUANTITY : ";
								cin>>quantity;
								C[set-1].setquantity(quantity);
								C[set-1].select();
								D.cal(B,C[set-1]);
								break;
						case 2:
								C[set-1].edit(quantity);
								quantity = 0;//delete order
								C[set-1].setquantity(quantity);
								break;				
						case 0: 
								break;				
						default:
								cout<<"						INVALID INPUT ,REENTER : ";
								pick =10;
								break;
					}			
					}while(pick == 10);
					break;	
		
			
		case  4 ://display current order	
					if( quantity == 0 )
					{
						cout<<"						HAVEN'T ORDER YET !\n";
						break;
					}		
					D.display(B,C[set-1]);				
					break;
		case  5  : //check seat available 
					int option;
					for(int i = 0; i < 8 ; i++)
					{
						if( A[i].counter != 1)
							cout<<"						"<<i+1<<". "<<A[i].getmovie()<<endl;
					}
					cout<<"						ENTER CODE TO CHECK MOVIE SEAT : ";
					do{
					cin>>option;
					cin.sync();
					if(option == 0)
						break;
					}while( A[option-1].counter == 1 );
				    cout<<"\n                                                   MOVIE :| "<<A[option-1].getmovie()<<"  |\n";		
					C[option-1].seatdisplay();
					break;	
		case  6 ://comfirm order
					if( quantity == 0)
					{
						cout<<"						HAVEN'T ORDER YET !\n";
						break;
					}
					D.receipt(B,C[set-1]);	
					D.setdata(B,C[set-1]);
					E[extracounter-1].setdata(D);
					grand = grand + E[extracounter-1].gettotal() ;
					quantity = 0;//counter set new order to initial 
					extracounter++;
					break;
		
		case 7  : //edit movie available
					int option1;
					do{
					cout<<"						1.Edit Movie."<<endl;
					cout<<"						2.Order History/Daily Sales."<<endl;
					cout<<"						0.Return Main."<<endl;
					cout<<"						";
					cin>>option1;
					
					if( option1 == 1)
						{
							cout<<"						1.REPLACE MOVIE"<<endl;
							cout<<"						2.ADD MOVIE"<<endl;
							cout<<"						3.REMOVE MOVIE"<<endl;
							cin>>replace;
					
							if( replace == 1)
							{
								cout<<"						TO REPLACE ENTER SELECT TO CHANGE :";
								cin>>replace;
								cin.sync();
								cout<<"						ENTER NAME ,CODE AND PRICE :";
								cin>>add>>code>>a_price;
								A[replace-1]={add,code,a_price};
								break;			
							}
								
							else if( replace == 2)		
							{
								cout<<"						TO ADD NEW MOVIE  ";
								cout<<"						ENTER NAME ,CODE AND PRICE :";
								cin.sync();
								cin>>add>>code>>a_price;									
								A[def++]={add,code,a_price};
								break;							
							}
							else if( replace == 3)
								{
									cout<<"						TO REMOVE MOVIE ";
									cout<<"						ENTER MOVIE CODE : ";
									cin>>replace;
									cin.sync();
									A[replace-1]={1};		
									break;
								}
							else
								{
									cout<<"						INVALID INPUT! RETURN TO MAIN."<<endl;
									break;	
								}			
								
						}
					else if( option1 == 2)
						{
								cout<<"						===========================================================================================\n";			
								cout<<"						~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~DAILY $ALE$~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
								cout<<"						===========================================================================================\n";			
								cout<<"						ORD         MOVIE               CODE             PRICE       QUANTITY      TOTAL     SEATno\n";
								for(int i = 0 ; i < extracounter ;i++)
								{
									if(E[i].gettotal() != 0)
									{
										cout<<"						";
										cout<<i+1;
										E[i].display();
									}
								}				
								cout<<fixed<<setprecision(2)<<"\n"<<setw(87)<<"						GRAND TOTAL : "<< grand<<endl;				
								break;
					}
					else if( option1 == 0)
							{
								option1 = 1;
								break;
							}
								
					}while(option1 != 1 || option1 != 2 );
					break;			
		case  0 :	//exit program
					choice = 111;
					break;						
	}			
	}while( choice != 111);	

	delete[] A;//delete dynamic memory allocated for array of object movie
	delete[] C;
}
