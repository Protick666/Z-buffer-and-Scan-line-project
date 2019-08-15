#include <bits/stdc++.h>
#include <math.h>
#include "bitmap_image.hpp"
using namespace std;
////https://github.com/andrewaeva/DGA
#define  ll  long long int
#define max3(a, b, c) max(a, b) > max(b, c) ? max(a, b) : max(b, c)
#define min3(a, b, c) min(a, b) < min(b, c) ? min(a, b) : min(b, c)
#define digit(c) (c - '0')
#define cc(c) (c - 'a')
#define pb push_back
#define mp make_pair
#define fi first+
#define se second
#define flag(i) cout<<"case "<<i<<endl;
#define all(X) X.begin(), X.end()
#define loop(i,n) for ( i=0; i<ll(n); i++ )
#define fr(i,x,y) for ( i=x; i<=y; i++ )
#define fur(i,x,y) for ( i=x; i>=y; i-- )
#define out(x) printf("%lld ",x);

#define in(x) scanf("%lld",&x);
#define in2(x,y) scanf("%lld%lld",&x,&y);
#define tt(x) cout<<"reached here "<<x<<endl;
#define REP1(i,a,b) for ( ll i=(a); i<=ll(b); i++ )
#define FOR(it,c) for ( auto it=(c).begin(); it!=(c).end(); it++ )
#define mp make_pair
#define ex  exit(0)
#define LSOne(S) (S & (-S))
#define INF INT_MAX //Infinity
#define cont continue
#define nl cout<<endl
#define modd 1000000007
//#define jj(x,y,v) v[x].pb(y);v[y].pb(x)
#define inv 10000000000
#define zz 1000000007
#define PI 3.14159265
////double z_buffer[1002][1002];
double x_block;
double y_block;
double top_y;
double left_x;

class config
{
public:
    int width;
    int height;
    double bottom_x;
    double bottom_y;
    double z_front;
    double z_rear;
    config(int a,int b,double x,double y,double z,double u)
    {
        this->width=a;
        this->height=b;
        this->bottom_x=x;
        this->bottom_y=y;
        this->z_front=z;
        this->z_rear=u;
    }
};

int countlines()
{
    FILE* myfile = fopen("stage3.txt", "r");
    int ch, number_of_lines = 0;

    do
    {
        ch = fgetc(myfile);
        if(ch == '\n')
            number_of_lines++;
    }
    while (ch != EOF);


    if(ch != '\n' && number_of_lines != 0)
        number_of_lines++;

    fclose(myfile);

    return number_of_lines;
}

class point
{
public:
    double x,y,z;
    point() {}
    point(double x,double y,double z)
    {
        this->x=x;
        this->y=y;
        this->z=z;
    }
    void pro()
    {
        cout<<this->x<<" "<<this->y<<endl;
    }


};


class triangle
{
public:
    point points[3];
    int color[3];
    triangle(point a,point b,point c)
    {
        this->points[0]=a;
        this->points[1]=b;
        this->points[2]=c;
    }
    triangle(point a,point b,point c,int x,int y,int z)
    {
        this->points[0]=a;
        this->points[1]=b;
        this->points[2]=c;
        this->color[0]=x;
        this->color[1]=y;
        this->color[2]=z;

    }

    triangle() {}

    void pro()
    {

        for(int i=0;i<3;i++)
            this->points[i].pro();
    }

};


vector<triangle> alltriangle;

ll find_top(triangle x,config cf)
{
    double p=top_y;
    //cout<<x.points[0].y<<" "<<x.points[1].y<<" "<<x.points[2].y<<endl;
    for(int i=0; i<cf.height; i++,p-=y_block)
    {
        //cout<<"p: "<<p<<endl;
        if((x.points[0].y<=p && x.points[1].y>=p) || (x.points[0].y>=p && x.points[1].y<=p))
            return i;
        if((x.points[1].y<=p && x.points[2].y>=p) || (x.points[1].y>=p && x.points[2].y<=p))
            return i;
        if((x.points[0].y<=p && x.points[2].y>=p) || (x.points[0].y>=p && x.points[2].y<=p))
            return i;
    }
    //cout<<"reverse";
}

ll find_bot(triangle x,config cf,ll bg)
{
    double p=top_y-y_block*(cf.height-1);
    for(int i=cf.height-1; i>=0; i--,p+=y_block)
    {
        if((x.points[0].y<=p && x.points[1].y>=p) || (x.points[0].y>=p && x.points[1].y<=p))
            return i;
        if((x.points[1].y<=p && x.points[2].y>=p) || (x.points[1].y>=p && x.points[2].y<=p))
            return i;
        if((x.points[0].y<=p && x.points[2].y>=p) || (x.points[0].y>=p && x.points[2].y<=p))
            return i;
    }

}
vector<pair<double,double> > intersection;

double ck_z(double x_val)
{
    double x1=intersection[0].first;
    double z1=intersection[0].second;

    double x2=intersection[intersection.size()-1].first;
    double z2=intersection[intersection.size()-1].second;
    return ((z2-z1)/(x2-x1))*(x_val-x1)+z1;
}

void ck(point a,point b,double yy)
{
    double x1=a.x;double y1=a.y;double z1=a.z;
    double x2=b.x;double y2=b.y;double z2=b.z;

    double t=(yy-y1)/(y2-y1);
    double x=x1+t*(x2-x1);
    double z=z1+t*(z2-z1);
    intersection.push_back(make_pair(x,z));
}
void ck_intersection(triangle x,double yy)
{
    intersection.clear();

    if((x.points[0].y<=yy && x.points[1].y>=yy) || (x.points[0].y>=yy && x.points[1].y<=yy))
        {
            ck(x.points[0],x.points[1],yy);
        }
    if((x.points[1].y<=yy && x.points[2].y>=yy) || (x.points[1].y>=yy && x.points[2].y<=yy))
        {
            ck(x.points[1],x.points[2],yy);
        }
    if((x.points[0].y<=yy && x.points[2].y>=yy) || (x.points[0].y>=yy && x.points[2].y<=yy))
        {
            ck(x.points[0],x.points[2],yy);
        }

}
int main()
{

    freopen("config.txt", "r", stdin);
    ll n,i,t,j,m,k,p,q,a,b;

    cin>>a>>b;

    double x,y,z,u;
    cin>>x>>y>>z>>u;

    config cf(a,b,x,y,z,u);

    ll totline=countlines();

    ll tot_tri=totline/3;
    cout<<tot_tri<<endl;
    freopen("stage3.txt", "r", stdin);

     // define the range


    //std::cout << distr(eng)

    bitmap_image image(cf.width,cf.height);

    for(int i=0;i<cf.width;i++){
        for(int j=0;j<cf.height;j++){
            image.set_pixel(i,j,0,0,0);
        }
    }





    /***
    for(int i=1; i<=tot_tri; i++)
    {
        string a,b,c;
        double x,y,z;
        triangle tr;

        for(int j=0; j<3; j++)
        {
            //cin>>x>>y>>z;
            cin>>a>>b>>c;
            point pp(x,y,z);

            cout<<a<<" "<<b<<" "<<c<<" "<<"hello"<<endl;

            //if(x<0)
                //cout<<"ya its true"<<endl;
            tr.points[j]=pp;
        }
        cout<<endl;
        tr.color[0]=distr(eng);
        tr.color[1]=distr(eng);
        tr.color[2]=distr(eng);

        alltriangle.push_back(tr);

    }

    ****/

    std::ifstream ifile("stage3.txt", std::ios::in);
    std::vector<double> scores;

    //check to see that the file was opened correctly:
    if (!ifile.is_open()) {
        std::cerr << "There was a problem opening the input file!\n";
        exit(1);//exit or do additional error checking
    }

    double num = 0.0;
    //keep storing values from the text file so long as data exists:
    while (ifile >> num) {
        scores.push_back(num);
    }
    tot_tri=scores.size()/9;

    double a1,b1,c1;
    a1=0;b1=1;c1=2;
    for(int i=1; i<=tot_tri; i++)
    {

        double x,y,z;
        triangle tr;

        for(int j=0; j<3; j++)
        {
            //cin>>x>>y>>z;
            //cin>>a>>b>>c;
            point pp(scores[a1],scores[b1],scores[c1]);
            a1+=3;b1+=3;c1+=3;

            ////cout<<a<<" "<<b<<" "<<c<<" "<<"hello"<<endl;

            //if(x<0)
                //cout<<"ya its true"<<endl;
            tr.points[j]=pp;
        }
        cout<<endl;
        /*std::random_device rd;     // only used once to initialise (seed) engine
std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
std::uniform_int_distribution<int> uni(0,255); // guaranteed unbiased

*/
        tr.color[0]=0 + (rand() % static_cast<int>(255 - 0 + 1));
        tr.color[1]=0 + (rand() % static_cast<int>(255 - 0 + 1));
        tr.color[2]=0 + (rand() % static_cast<int>(255 - 0 + 1));

        alltriangle.push_back(tr);

    }

    //verify that the scores were stored correctly:
    //for (int i = 0; i < scores.size(); ++i)
       // cout<<scores[i]<<endl<<" "<<"ola";


    double ** z_buffer = new double*[cf.width];
        for(int i =0; i<cf.width;i++){
               z_buffer[i] = new double[cf.height];

                ////a[i] = new int[colCount];
            }


    for(int i=0; i<cf.width; i++)
        for(j=0; j<cf.height; j++)
            z_buffer[i][j]=cf.z_rear + 1;

    x_block=2*(-cf.bottom_x)/cf.width;
    y_block=2*(-cf.bottom_y)/cf.height;
    //Top_y= 1-dy/2, Left_x= -1+dx/2

    top_y=-cf.bottom_y-(y_block/2);
    left_x=cf.bottom_x+(x_block/2);

        //cout<<"hello";
    for(int i=0; i<tot_tri; i++)
    {
        double x_min,x_max,y_min,y_max,z_min,z_max;

        x_min=min3(alltriangle[i].points[0].x,alltriangle[i].points[1].x,alltriangle[i].points[2].x);
        y_min=min3(alltriangle[i].points[0].y,alltriangle[i].points[1].y,alltriangle[i].points[2].y);
        z_min=min3(alltriangle[i].points[0].z,alltriangle[i].points[1].z,alltriangle[i].points[2].z);

        x_max=max3(alltriangle[i].points[0].x,alltriangle[i].points[1].x,alltriangle[i].points[2].x);
        y_max=max3(alltriangle[i].points[0].y,alltriangle[i].points[1].y,alltriangle[i].points[2].y);
        z_max=max3(alltriangle[i].points[0].z,alltriangle[i].points[1].z,alltriangle[i].points[2].z);

        if(x_min>-cf.bottom_x || x_max<cf.bottom_x)
            cont;
        if(y_min>-cf.bottom_y || y_max<cf.bottom_y)
            cont;
        if(z_min>cf.z_rear || z_max<cf.z_front)
            cont;

           //// cout<<"done1";

        ll top_line=find_top(alltriangle[i],cf);
        ll bot_line=find_bot(alltriangle[i],cf,top_line);
        alltriangle[i].pro();
        cout<<"triangle no "<<i<<endl;
        cout<<tot_tri<<endl;
        cout<<top_line<<" "<<bot_line<<" "<<top_y<<y_block<<endl;


        for(int ii=top_line; ii<=bot_line; ii++)
        {
            double y_depth=top_y-y_block*ii;
            ck_intersection(alltriangle[i],y_depth);

            sort(all(intersection));
            double right_bound=left_x+(cf.width-1)*(x_block);
            int p,q;//// p=left col, q= right col
            cout<<"11"<<endl;

            //top_y=-cf.bottom_y-(y_block/2);
            //left_x=cf.bottom_x+(x_block/2);
            if(intersection[0].first<left_x)
            {
                p=0;
            }
            else
            {
                double tucker=intersection[0].first-left_x;
                int temp=tucker/x_block;
                if(intersection[0].first>left_x+temp*x_block)
                    temp++;
                p=temp;
            }

            if(intersection[intersection.size()-1].first>right_bound)
            {
                q=cf.width-1;
            }
            else
            {
                double h=((cf.width-1)*x_block+left_x-intersection[intersection.size()-1].first);

                int temp=h/x_block;
                if(h>temp*x_block)
                    temp++;
                q=cf.width-1-(temp);
            }
            //cout<<"22"<<endl;
            //cout<<"ss"<<endl;

           // cout<<p<<" "<<q<<endl;

            for(int j=p;j<=q;j++)
            {
                double xx=left_x+(j)*(x_block);
                //cout<<"ck1"<<endl;
                double z_val=ck_z(xx);
                //cout<<"ckdone"<<endl;
                //cout<<j<<" "<<ii<<" ola"<<endl;
                //cout<<cf.width<<" "<<cf.height<<endl;
                if(z_buffer[j][ii]>z_val && (z_val>=cf.z_front && z_val<=cf.z_rear))
                {
                    z_buffer[j][ii]=z_val;
                     image.set_pixel(j,ii,alltriangle[i].color[0],alltriangle[i].color[1],alltriangle[i].color[2]);

                }


            }

            //cout<<"pp"<<endl;


        }

    }

    image.save_image( "1.bmp" );

    freopen("z_buffer.txt", "w", stdout);

    for(int i=0; i<cf.width; i++){
         for(j=0; j<cf.height; j++)
         {
             cout<<z_buffer[i][j]<<" ";
         }
         cout<<endl;
    }


  for(int i = 0; i <cf.width; ++i)
  {
     delete z_buffer[i];
  }

  delete[] z_buffer;

  delete &image;


    intersection.clear();
    scores.clear();
    alltriangle.clear();







}
