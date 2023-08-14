#include <bits/stdc++.h>
using namespace std;

class Integer
{
    private:
    vector<int> v;
    string s1;
    public:
    Integer(){};
    ~Integer(){};
   /* Integer(const string s)
    {
        for(int i=0;i<(int)s.size();i++)
        {
            if(s[i]=='-')
            {
                i++;
                
                v.push_back(-1*(s[i]-'0'));
            }
            else
               v.push_back(s[i]-'0');
                
             
        } 
    }*/
    Integer operator+( Integer & );
    Integer operator-( Integer & );
    friend void sub_fun(int & i ,Integer & i3 , Integer  &a1 , Integer  &a2);
    bool operator==(Integer&);
    bool operator!=(Integer&);
    bool operator<(Integer&);
    bool operator<=(Integer&);
    bool operator>(Integer&);
    bool operator>=(Integer&);
    Integer& operator+=(Integer&);
    Integer& operator-=(Integer&);
    Integer operator*( Integer&) ;
    Integer operator/( Integer&)  ;
    Integer operator%( Integer&)  ;
    Integer& operator*=(Integer&);
    Integer& operator%=(Integer&);
    Integer& operator/=(Integer&);
    friend ostream& operator<<(ostream&, Integer&);
    friend istream& operator>>(istream&, Integer&);
    void set_vector(string  s1);
    void set_string(vector<int> v);
    
    
    
    void show();
    
};


istream& operator>>(istream& in, Integer& a2)
{
        
        in>>a2.s1;
        a2.set_vector(a2.s1);
        return in;
}

ostream& operator<<(ostream& out, Integer& a2)
{
     
     out<<a2.s1;
     a2.set_string(a2.v);
     out<<a2.s1;   
     return out;   
}


void Integer::set_vector(string  s1)
{
    
    for(int i=0;i<(int)s1.size();i++)
        {
            if(s1[i]=='-')
            {
                i++;
                v.push_back(-1*(s1[i]-'0'));
            }
            else
               v.push_back(s1[i]-'0');
        } 
}


void Integer::set_string(vector<int> v)
{
    if(v[0]<0)
    { 
        s1.push_back('-');
        v[0]*=-1;
     }    
    
    for(int i=0;i<(int)v.size();i++)
    {    
        s1.push_back(v[i]+'0');
    }    
}

void sub_fun(int & i ,Integer & i3 , Integer  &a1 , Integer  &a2)
{
    for(;i<(int)a2.v.size();i++)
            {
                if(a1.v[i]<a2.v[i])
                {
                    int j=i+1;
                    while(a1.v[j]==0)
                      j++;
                                     
                    a1.v[j]--;
                    j--;
                    
                    while(j!=i)
                    {
                       a1.v[j]=9;
                        j--;
                    }
                    
                    a1.v[i]+=10;
                    
                }
                       
                i3.v.push_back(a1.v[i]-a2.v[i]);
            }
}

//start of + fn for big integers
Integer Integer::operator+( Integer & a2)
{
    Integer i3;
    int carry=0;
    int sum=0;
    int i=0;   
    
    if(v[0]>0 && a2.v[i]<0)
    {   // add a+b where b is -ve so a-b
        a2.v[0]*=-1;
        i3=(*this)-a2;
        a2.v[0]*=-1;
    }
    
    else if(v[0]<0 && a2.v[i]>0)
    {   // add -a+b  which is b-a
        v[0]*=-1;
        i3=a2-(*this);
        v[0]*=-1;
    }
    
    else if(v[0]<0 && a2.v[i]<0)
    {
        v[0]*=-1;
        a2.v[0]*=-1;
        i3=(*this)+a2;
        i3.v[0]*=-1;
        v[0]*=-1;
        a2.v[0]*=-1;
    }
    
    else
    {    
    
        reverse(v.begin(),v.end());
        reverse(a2.v.begin(),a2.v.end());



        for( ;i<(int)min(v.size(),a2.v.size());i++)
        {
                sum=a2.v[i] + v[i] + carry;
                carry=sum/10;
                sum%=10;
                i3.v.push_back(sum);
        }

        if(v.size()>a2.v.size())
        {
            for( ;i<(int)v.size();i++)
            {
                sum=v[i]+carry;
                carry=sum/10;
                sum%=10;
                i3.v.push_back(sum);
            } 

        }

        if(v.size()<a2.v.size())
        {
            for( ;i<(int)a2.v.size();i++)
            {
                sum=a2.v[i]+carry;
                carry=sum/10;
                sum%=10;
                i3.v.push_back(sum);
            } 

        }


       if(carry!=0)
            i3.v.push_back(carry);

        reverse(i3.v.begin(),i3.v.end());
        reverse(v.begin(),v.end());
        reverse(a2.v.begin(),a2.v.end());
    
    }

    return i3;
}
//end of + fn for big integers


//start of - fn for big integers
Integer Integer::operator-( Integer & a2)
{
    Integer i3;
    int i=0;
    
    if(a2.v[0]<0 && v[0]>0)
    {   // to do a-b where b is -ve so it will be a+b
       a2.v[0]*=-1;
       i3=*this+a2;
       a2.v[0]*=-1;
    }  
    
    else if(v[0]<0 && a2.v[0]>0)
    {   // to do a-b where a is -ve so it is -a-b = -(a+b)
        v[0]*=-1;
        i3=*this+a2;
        i3.v[0]*=-1;
        v[0]*=-1;
    }
    
    else if(v[0]<0 && a2.v[0]<0)
    {
        //to do a-b where a and b both -ve so its b-a;
        
        a2.v[0]*=-1;
        v[0]*=-1;
        i3=a2-(*this);
        a2.v[0]*=-1;
        v[0]*=-1;
        
        
    }
    
   
    
    else
    {    //to do a-b      where both a abd b are positive;
        
        Integer i1,i2;
        for(int i=0;i<(int)v.size();i++)
            i1.v.push_back(v[i]);
        for(int i=0;i<(int)a2.v.size();i++)
            i2.v.push_back(a2.v[i]);
        
    
        
        reverse(v.begin(),v.end());
        reverse(a2.v.begin(),a2.v.end());

        if(a2.v.size()<v.size())
        {

            sub_fun(i ,i3 , (*this) , a2);
           
            for(;i<(int)v.size();i++)
                 i3.v.push_back(v[i]);
            
            if(i3.v[i3.v.size()-1]==0)
                i3.v.pop_back();
            reverse(i3.v.begin(),i3.v.end());
            
            

         }

        else if(a2.v.size()>v.size())
        {

            sub_fun(i ,i3 , a2,(*this) );
            for(;i<(int)a2.v.size();i++)
                i3.v.push_back(a2.v[i]);


            if(i3.v[i3.v.size()-1]==0)
                i3.v.pop_back();
            reverse(i3.v.begin(),i3.v.end());
            i3.v[0]*=-1;
        }

        else
        {

            reverse(v.begin(),v.end());
            reverse(a2.v.begin(),a2.v.end());

            int i=0;
            while(v[i]==a2.v[i] && i<(int)v.size())
                i++;
            if(i==(int)v.size())
                i3.v.push_back(0);

            else if(v[i]>a2.v[i])
            {
                i=0;
                reverse(v.begin(),v.end());
                reverse(a2.v.begin(),a2.v.end());

                sub_fun(i ,i3 , (*this) , a2);

                auto it = --i3.v.end();
                while(it!=v.begin() && *it==0  )
                {
                    i3.v.pop_back();
                    it--;

                }

                reverse(i3.v.begin(),i3.v.end());



            }

            else
            {
                i=0;
                reverse(v.begin(),v.end());
                reverse(a2.v.begin(),a2.v.end());

                sub_fun(i ,i3 ,a2 ,(*this)); 
                auto it = --i3.v.end();
                while(it!=v.begin() && *it==0  )
                {
                    i3.v.pop_back();
                    it--;

                }

                reverse(i3.v.begin(),i3.v.end());
                i3.v[0]*=-1;

            }



        }
       
       // reverse(v.begin(),v.end());
        //reverse(a2.v.begin(),a2.v.end());
        v.clear();
        a2.v.clear();
        for(int i=0;i<(int)i1.v.size();i++)
            v.push_back(i1.v[i]);
        for(int i=0;i<(int)i2.v.size();i++)
            a2.v.push_back(i2.v[i]);
        
         
    }
   
   
    
        return i3;
    
}

//end of - function 

//bool to compare ==
bool Integer::operator==(Integer& a2)
{
    if(v.size()!=a2.v.size())
        return false;
    else
    {
        for(int i=0;i<(int)v.size();i++)
            if(v[i]!=a2.v[i])
                return false;
        
        return true;
    }
    
}

// bool to compare !=
bool Integer::operator!=(Integer& a2)
{
    bool x;
    x=(*this)==a2;
    return (!x);
}

//bool to 
bool Integer::operator<(Integer& a2)
{
    if((v[0]>0 && a2.v[0]>0) && v.size()<a2.v.size())
        return true;
    else if((v[0]>0 && a2.v[0]>0) && v.size()>a2.v.size())
        return false;
    else if(v[0]>0 && a2.v[0]<0) 
        return false;
    else if(v[0]<0 && a2.v[0]>0)
        return true;
    else if(v.size()==a2.v.size())
      {   if((v[0]>0 && a2.v[0]>0))
        {  for(int i=0 ;i<(int)v.size();i++)
              { if(v[i]==a2.v[i])
                   {   if(i==(int)v.size())
                        break;
                      else
                      continue;
                  } 
                else if(v[i]<a2.v[i])
                   return true;
                else 
                   return false;
              } 
            return false;
        }
     
     else if((v[0]<0 && a2.v[0]<0))
     {
         {  for(int i=0 ;i<(int)v.size();i++)
              { if(v[i]==a2.v[i])
                  {   if(i==(int)v.size())
                        break;
                      else
                      continue;
                  } 
                else if(v[i]<a2.v[i])
                   return false;
                else 
                   return true;
              } 
            return false;
        }
         
     }
     
     
        
        
    }
    
    return false;
    
}


bool Integer::operator<=(Integer& a2)
{
    if((v[0]>0 && a2.v[0]>0) && v.size()<a2.v.size())
        return true;
    else if((v[0]>0 && a2.v[0]>0) && v.size()>a2.v.size())
        return false;
    else if(v[0]>0 && a2.v[0]<0) 
        return false;
    else if(v[0]<0 && a2.v[0]>0)
        return true;
    else if(v.size()==a2.v.size()) 
    {   if((v[0]>0 && a2.v[0]>0))
        {  for(int i=0 ;i<(int)v.size();i++)
              { if(v[i]==a2.v[i])
                   continue;
                else if(v[i]<a2.v[i])
                   return true;
                else 
                   return false;
              } 
            return true;
        }
     
     else if((v[0]<0 && a2.v[0]<0))
     {
         {  for(int i=0 ;i<(int)v.size();i++)
              { if(v[i]==a2.v[i])
                   continue;
                else if(v[i]<a2.v[i])
                   return false;
                else 
                   return true;
              } 
            return true;
        }
         
     }
     
     
        
        
    }
    
    return true;
    
     
    
}

bool Integer::operator>(Integer & a2)
{
    bool x= (*this)<=a2;
    return !x;
}

bool Integer::operator>=(Integer & a2)
{
    bool x= (*this)<a2;
    return !x;
}


Integer& Integer::operator+=(Integer &a2)
{
    (*this)=(*this)+a2;
    return *this;
} 

Integer& Integer::operator*=(Integer &a2)
{
    (*this)=(*this)*a2;
    return *this;
} 


Integer& Integer::operator-=(Integer &a2)
{
    (*this)=(*this)-a2;
    return *this;
} 

Integer& Integer::operator/=(Integer &a2)
{
    (*this)=(*this)/a2;
    return *this;
} 


Integer& Integer::operator%=(Integer &a2)
{
    (*this)=(*this) % a2;
    return *this;
} 

//fn for mutiplication 
Integer Integer::operator*( Integer & a2) 
{
    int count2 = a2.v.size(); // a2 ka size 
    int count1 = v.size();
    int num;
    Integer i3;
    int mul;
    int carry=0;
    int j=count2-1,i;
    int flag1=0,flag2=0;
    
    if(v[0]<0 && a2.v[0]>0 )
    {
       flag1=1;
        v[0]*=-1;
    }
    
    else if(v[0]>0 && a2.v[0]<0)
    {
        flag2=1;
        a2.v[0]*=-1;
    }
    
    else if(v[0]<0 && a2.v[0]<0)
    {
        flag2=1;
        flag1=1;
        v[0]*=-1;
        a2.v[0]*=-1;
    }
    
    // do 1 time 
    num=a2.v[j];
        for(i = count1-1;i>=0;i--)
        {
            mul=v[i]*num+carry;
            carry=mul/10;
            mul=mul%10;
            i3.v.push_back(mul);
        }
        if(carry!=0)
            i3.v.push_back(carry);
        reverse(i3.v.begin(),i3.v.end());
    
    
    
    //for rest n-1 digit 
    for(j= count2-2;j>=0;j--)
    {   carry=0;
        Integer i4;
        num=a2.v[j];
        for(int k= 1 ;k<=count2-1-j;k++)
            i4.v.push_back(0);
        
        for(i = count1-1;i>=0;i--)
        {
            mul=v[i]*num+carry;
            carry=mul/10;
            mul=mul%10;
            i4.v.push_back(mul);
        }
        if(carry!=0)
            i4.v.push_back(carry);
        
        reverse(i4.v.begin(),i4.v.end());
       
        
        i3+=i4;   
            
             
    }
    
    if(flag1==1)
    {
        v[0]*=-1;
        i3.v[0]*=-1;
        
    }
    
    if(flag2==1)
    {
        a2.v[0]*=-1;
        i3.v[0]*=-1;
        
    }
    
    
    return i3;
}

//fn for a/b 
Integer Integer::operator/( Integer &  a2) 
{
    Integer check;
    Integer rem;
    Integer temp;
    Integer qot;
    int i;
    int flag1=0,flag2=0;
    
    if(v[0]<0 && a2.v[0]>0 )
    {
       flag1=1;
        v[0]*=-1;
    }
    
    else if(v[0]>0 && a2.v[0]<0)
    {
        flag2=1;
        a2.v[0]*=-1;
    }
    
    else if(v[0]<0 && a2.v[0]<0)
    {
        flag2=1;
        flag1=1;
        v[0]*=-1;
        a2.v[0]*=-1;
    }
   
    if(*(this)<a2)
        qot.v.push_back(0);
    else if(*(this)==a2)
        qot.v.push_back(1);
    else 
    {
        
        for(i=0;i<(int)a2.v.size();i++)
            temp.v.push_back(v[i]);
        
        if(temp < a2)
        {   temp.v.push_back(v[i]);
            i++;
        }
        
        
        //to check the multiple which divide 
        for(int i=2;i<=10;i++)
        {
            
            Integer in;
            in.v.push_back(i);
            check = a2 * in;
            if(check>temp)
            {
                check-=a2;
                qot.v.push_back(i-1);
                rem=temp-check;
                break;
            }
            
        }
        
        while(i!=(int)v.size())
        {
       
            do 
            {
               rem.v.push_back(v[i]);
               if(rem<a2)
               { qot.v.push_back(0);
                 i++;
               }
                else
                {
                    i++;
                    break;
                }
                
                 
            } while(rem<a2  && i!=(int)v.size());
            
          
            temp.v.clear();
            for(int i=0;i<(int)rem.v.size();i++)
            temp.v.push_back(rem.v[i]);
     
            if(temp>a2)
            {    
                for(int i=2;i<=10;i++)
                {
            
                    Integer in;
                    in.v.push_back(i);
                    check = a2 * in;
                    if(check>temp)
                    {
                        check-=a2;
                        qot.v.push_back(i-1);
                        rem=temp-check;
                        break;
                    }
            
                }
            }
        }
        
        
        //cout<<"rem hai yhe ";
       //rem.show(); 
        
        
    }
    
    if(flag1==1)
    {
        v[0]*=-1;
        qot.v[0]*=-1;
        
    }
    
    if(flag2==1)
    {
        a2.v[0]*=-1;
        qot.v[0]*=-1;
        
    }
    
    return qot;
}
// fn end for / 


// fn for % 

Integer Integer::operator%( Integer &  a2) 
{
    Integer check;
    Integer rem;
    Integer temp;
    Integer qot;
    int i;
    int flag1=0,flag2=0;
    if(v[0]<0 && a2.v[0]>0 )
    {   
        //a%b a is -ve b is +ve
        flag1=1;
        v[0]*=-1;
    }
    
    else if(v[0]>0 && a2.v[0]<0)
    {   //a%b a is +ve b is -ve
        flag2=1;
        a2.v[0]*=-1;
    }
    
    else if(v[0]<0 && a2.v[0]<0)
    {  //both negative 
        flag2=1;
        flag1=1;
        v[0]*=-1;
        a2.v[0]*=-1;
    }
    
    if(*(this)<a2)
    {
       qot.v.push_back(0); 
        for(int i=0;i<(int)v.size();i++)
            rem.v.push_back(v[i]);
    }
        
    else if(*(this)==a2)
    {   
        qot.v.push_back(1);
        rem.v.push_back(0);
        
    }
    else 
    {
        for(i=0;i<(int)a2.v.size();i++)
            temp.v.push_back(v[i]);
        
        if(temp < a2)
        {   temp.v.push_back(v[i]);
            i++;
        }
        
        
        //to check the multiple which divide 
        for(int i=2;i<=10;i++)
        {
            
            Integer in;
            in.v.push_back(i);
            check = a2 * in;
            if(check>temp)
            {
                check-=a2;
                qot.v.push_back(i-1);
                rem=temp-check;
                break;
            }
            
        }
        
        
        
        while(i!=(int)v.size())
        {
           
             do 
            {
               rem.v.push_back(v[i]);
               if(rem<a2)
               { qot.v.push_back(0);
                 i++;
               }
                else
                {
                    i++;
                    break;
                }
                
                 
            } while(rem<a2  && i!=(int)v.size());
            
 
            temp.v.clear();
            for(int i=0;i<(int)rem.v.size();i++)
            temp.v.push_back(rem.v[i]);
            

        
            if(temp>a2)
            {    
                for(int i=2;i<=10;i++)
                {
            
                    Integer in;
                    in.v.push_back(i);
                    check = a2 * in;
                    if(check>temp)
                    {
                        check-=a2;
                        qot.v.push_back(i-1);
                        rem=temp-check;
                        break;
                    }
            
                }
            }
        }

    }
    
    if(flag1==1 && flag2==1)
    {
        v[0]*=-1;
        a2.v[0]*=-1;
        qot.v[0]*=-1;
        rem.v[0]*=-1;
        
    }
    
    else if(flag2==1 && flag1==0)
    {
        a2.v[0]*=-1;
        qot.v[0]*=-1;
        
        
    }
    
    else if(flag1==1 && flag2==0)
    {
        v[0]*=-1;
        qot.v[0]*=-1;
        rem.v[0]*=-1;
    }
    
    
    reverse(rem.v.begin(),rem.v.end());
    auto it = --rem.v.end();
    while(it!=rem.v.begin() && *it==0  )
    {
        rem.v.pop_back();
        it--;

    }
    reverse(rem.v.begin(),rem.v.end());
    
    
    
    return rem;
}

void Integer::show()
{
    for(auto val:v)
        cout<<val;
    cout<<endl;

}



int main() {
   
    
    string op;
    //string s1,s2;
    cin>>op;
    
    
    
    while(op!="end")
    {
        Integer i1,i2,i3;
        cin>>i1>>i2;
        if(op=="+")
        {
            
            i3=i1+i2;
            cout<<i3<<endl;
        }
        else if(op=="-")
        {
            
            i3=i1-i2;
            cout<<i3<<endl;
        }
        else if(op=="*")
        {   
            i3=i1*i2;
            cout<<i3<<endl;
        }
        else if(op=="/")
        {   
            i3=i1/i2;
            i3.show();
        }
        else if(op=="%")
        {   
            i3=i1%i2;
            cout<<i3<<endl;
        }
        else if(op=="+=")
        {   
            i1+=i2;
            cout<<i1<<endl;
        }
        else if(op=="-=")
        {   
            i1-=i2;
            cout<<i1<<endl;
        }
        else if(op=="/=")
        {   
            i1/=i2;
            cout<<i1<<endl;
        }
        else if(op=="*=")
        {   
            i1*=i2;
            cout<<i1<<endl;
        }
        else if(op=="%=")
        {   
            i1%=i2;
            cout<<i1<<endl;
        }
        else if(op=="!=")
        {   
            bool result = (i1!=i2);
            if(result !=0)
                cout<<"true\n";
            else
                cout<<"false\n";
        }
         else if(op=="==")
        {   
            bool result = (i1==i2);
            if(result !=0)
                cout<<"true\n";
            else
                cout<<"false\n";
        }
         else if(op=="<")
        {   
            bool result = (i1<i2);
            if(result !=0)
                cout<<"true\n";
            else
                cout<<"false\n";
        }
         else if(op==">")
        {   
            bool result = (i1>i2);
            if(result !=0)
                cout<<"true\n";
            else
                cout<<"false\n";
        }
         else if(op=="<=")
        {   
            bool result = (i1<=i2);
            if(result !=0)
                cout<<"true\n";
            else
                cout<<"false\n";
        }
         else if(op==">=")
        {   
            bool result = (i1>=i2);
            if(result !=0)
                cout<<"true\n";
            else
                cout<<"false\n";
        }
        
        
     cin>>op;
        
    } 
       

    return 0;
}