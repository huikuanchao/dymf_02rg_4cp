#include "globals.h"
void  add_sol(int );
void  remove_sol();
int find_homoc();
bool deleteNode(struct Node **, Node *);


void flux(){

  int tmp_id,tmp_idc[Nhc];
  double cur_ratio = double(nsol)/double(nD*(Nda+Ndb)+nA*Nha + nB*Nhb +nC *Nhc + nsol +nP * ( 1 + ng_per_partic * ( Ng + 1 ) ) );
  if(flux_para <= 0 ) {
	cout<<"wrong flux setup!"<<endl;
       exit(1);
 }

  
  if((flux_para ==  1 )and (cur_ratio < eq_phisol) ){
	tmp_id = find_homoc();
	add_sol( tmp_id);

  }

   if(flux_para ==  2){
             
           remove_sol();
    
   }


}

int find_homoc(){
       struct Node *cur;
       int i,tp_cind ,ind1, ind2,  ind_t = nD*(Nda+Ndb) + nA*Nha +nB*Nhb + nP * ( 1 + ng_per_partic * ( Ng + 1 ) ) ;     
        double tmpz ;  

       
       for(i=0 ;i < nC ; i++){
	    
	     if(i == 0 ) cur = nC_ll_head;
	     else cur = cur->next;
             tp_cind = cur->data;
 	     ind1 = ind_t + tp_cind*Nhc;
	     ind2 = ind1 + Nhc-1;
             tmpz = (x[ind1][Dim-1] +x[ind2][Dim-1])/2.0 ;
	     if(tmpz >= flux_buffer){

	           deleteNode(&nC_ll_head,cur);	   
		   break;
		   
		   
             }
             if(i == nC-1) {
		cout<<"can not find C chain in the buffer"<<endl;
	        exit(1);
	     }
	}
       return tp_cind;       

}

void  add_sol(int ch_id ){

	
	int i, j,ind, ind_s,ind_t = nD*(Nda+Ndb) + nA*Nha +nB*Nhb + nP * ( 1 + ng_per_partic * ( Ng + 1 ) ) ;

	ind_s = ind_t + max_nC*Nhc +nsol;

        ind = ind_t + ch_id*Nhc;
        for(i = 0 ;i<Nhc ; i++ ){
		for(j =0 ;j<Dim; j++){
                 x[ind_s][j] = x[ind][j];

	        }
	    
	    nstot_flag[ind] = 0;
	    nstot_flag[ind_s] = 1;
            sol_flag[nsol+i] = 1;

	    x_bac[ind_s][0] = -1;
	    tp[ind_s]  = 4 ;
	    xc[ind_s] = "N" ;
	
	    ind_s +=1;
	    ind +=1;
	}
       
        nc_flag[ch_id] = 0;
	nsol += Nhc;
        nC -= 1;
         

}


void  remove_sol(){

     int i , j, min_sol=0,ind , ind_s = nD*(Nda+Ndb) + nA*Nha +nB*Nhb + nP * ( 1 + ng_per_partic * ( Ng + 1 ) )  + max_nC*Nhc ;
   
     for(i = 0 ; i< nsol ; i++){
           ind = ind_s + i;

	   if( x[ind][Dim-1]>flux_buffer){
		 nstot_flag[ind] = 0;
	   	 sol_flag[i] = 0;
	         min_sol  += 1;
	   }
     
        
     }


     nsol -= min_sol;


}


