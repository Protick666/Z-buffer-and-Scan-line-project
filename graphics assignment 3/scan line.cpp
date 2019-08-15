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
double bot_y;
double right_x;



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
class plane_eq
{
    public:
        double a,b,c,d;
};

class edge
{
 public:
      double x_at_yMIN,   y_MAX ,   dX,   ID;
      edge(double a,double b,double c,double d)
      {
          this->x_at_yMIN=a;
          this->y_MAX=b;
          this->dX=c;
          this->ID=d;
      }
      edge(){}
      void pro()
      {
          cout<<this->x_at_yMIN<<" "<<this->y_MAX<<" "<<this->dX<<" "<<this->ID<<endl;
      }

};

class active_edge
{
 public:
      double x_intersect,   y_MAX ,   dX,   ID;
      active_edge(double a,double b,double c,double d)
      {
          this->x_intersect=a;
          this->y_MAX=b;
          this->dX=c;
          this->ID=d;
      }
      active_edge(){}
};


class triangle
{
public:
    ll id;
    bool bl;
    point points[3];
    int color[3];
    plane_eq pq;
    triangle(point a,point b,point c)
    {
        this->points[0]=a;
        this->points[1]=b;
        this->points[2]=c;
        bl=false;
    }
    triangle(point a,point b,point c,int x,int y,int z)
    {
        this->points[0]=a;
        this->points[1]=b;
        this->points[2]=c;
        this->color[0]=x;
        this->color[1]=y;
        this->color[2]=z;
        bl=false;

    }

    triangle() {}

    void pro()
    {

        for(int i=0;i<3;i++)
            this->points[i].pro();
    }
    void plane_calc()
    {
        double ax,ay,az,bx,by,bz,cx,cy,cz;
        ax=this->points[0].x;
        ay=this->points[0].y;
        az=this->points[0].z;

        bx=this->points[1].x;
        by=this->points[1].y;
        bz=this->points[1].z;

        cx=this->points[2].x;
        cy=this->points[2].y;
        cz=this->points[2].z;

        this->pq.a=(by-ay)*(cz-az)-(cy-ay)*(bz-az);
        this->pq.b=(bz-az)*(cx-ax)-(cz-az)*(bx-ax);
        this->pq.c=(bx-ax)*(cy-ay)-(cx-ax)*(by-ay);
        this->pq.d=-((this->pq.a)*ax+(this->pq.b)*ay+(this->pq.c)*az);
    }

};

vector<active_edge> edge_active;
set<ll> polygon_active;
set<ll>::iterator it;



vector<triangle> alltriangle;
map<ll,triangle> tri_map;
vector<edge> alledge;
map<ll,vector<edge> > edge_map;

ll find_top(double y,config cf)
{
    double p=top_y;

    for(int i=0; i<cf.height; i++,p-=y_block)
    {
        if(p<y)
            return i;
    }

}

ll find_bot(double y,config cf)
{
    double p=top_y-y_block*(cf.height-1);
    for(int i=cf.height-1; i>=0; i--,p+=y_block)
    {
        if(p>y)
            return i;
    }
}




double  ck(point a,point b,double yy)
{
    double x1=a.x;double y1=a.y;double z1=a.z;
    double x2=b.x;double y2=b.y;double z2=b.z;

    double t=(yy-y1)/(y2-y1);
    double x=x1+t*(x2-x1);
    return x;
}

void make_edge(point a,  point b,  ll id,  config cf)
{
    ll y,yy;

    if(a.y<bot_y)
    {
        y=cf.height-1;
    }
    else
    {
        y=find_bot(a.y,  cf);
    }

    if(b.y>top_y)
        yy=0;
    else
        yy=find_top(b.y,  cf);

    ////cout<<"edge "<<y<<" "<<yy<<endl;

    double temp=yy*y_block+top_y;
    double del=(a.x-b.x)/(a.y-b.y);

    double x_at_min=ck(a,  b,  top_y-y_block*y);

    edge new_edge(x_at_min, top_y-y_block*yy,  del,  id);
    new_edge.pro();
    edge_map[y].push_back(new_edge);


}

struct less_than_key
{
    inline bool operator() (const edge struct1, const edge struct2)
    {
        return (struct1.x_at_yMIN<=struct2.x_at_yMIN);
    }
};

struct lesser
{
    inline bool operator() (const active_edge struct1, const active_edge struct2)
    {
        return (struct1.x_intersect<=struct2.x_intersect);
    }
};

////x_check(edge_active[i].x_intersect,edge_active[i+1].x_intersect,cf);
pair<ll, ll>  x_check(double x1,double x2,config cf)
{
    if(x2<left_x || x1>right_x)
        return make_pair(1,-1);

    x1=max(x1,left_x);
    x2=min(x2,right_x);
    double temp=x1-left_x;
    ll p1=temp/x_block;
    if(x1>p1*x_block+left_x)
        p1++;

    temp=right_x-x2;
     ll p2=temp/x_block;
     if(temp>p2*x_block)
        p2++;
    p2=cf.width-1-p2;
    if(p2<p1)
        p2=p1;

    return make_pair(p1,p2);
}

/////which_triangle(depth,left_x+mypair.first*x_block)

ll which_triangle(double y,double x, config cf)
{
    ll id=-1;
    double ref_z=cf.z_rear;

    for (it=polygon_active.begin(); it!=polygon_active.end(); ++it)
    {
        ll t=*it;
        triangle tri;
        tri=tri_map[t];
        double z_val=(-tri.pq.a*x-tri.pq.b*y-tri.pq.d)/tri.pq.c;
        if(z_val<=ref_z && z_val>=cf.z_front)
        {
            id=t;
            ref_z=z_val;
        }
    }
    return id;
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

     ll id=1;

      x_block=2*(-cf.bottom_x)/cf.width;
    y_block=2*(-cf.bottom_y)/cf.height;
    //Top_y= 1-dy/2, Left_x= -1+dx/2

    top_y=-cf.bottom_y-(y_block/2);
    left_x=cf.bottom_x+(x_block/2);
    bot_y=top_y-(cf.height-1)*y_block;
    right_x=left_x+(cf.width-1)*x_block;

    cout<<tot_tri<<" tot"<<endl;
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
        ////cout<<endl;

        tr.color[0]=0 + (rand() % static_cast<int>(255 - 0 + 1));
        tr.color[1]=0 + (rand() % static_cast<int>(255 - 0 + 1));
        tr.color[2]=0 + (rand() % static_cast<int>(255 - 0 + 1));
        tr.id=id;
        ////id++;
        tr.plane_calc();
        tri_map[id]=tr;
        alltriangle.push_back(tr);

        for(int j=0;j<3;j++)
        {
            for(k=j+1;k<3;k++)
            {
                point a;
                point b;
                a=tr.points[j];
                b=tr.points[k];
                cout<<"printing"<<endl;
                a.pro();
                b.pro();
                if(a.y>b.y)
                    swap(a,b);
                if(b.y<bot_y || a.y>top_y)
                    cont;
                 if(a.y == b.y)
                    cont;
                make_edge(a,b,id,cf);

            }
        }
        id++;

    }

    for(int i=0;i<cf.height;i++)
    {
            std::sort(edge_map[i].begin(), edge_map[i].end(), less_than_key());
    }


     double depth=top_y-(cf.height-1)*y_block;

     for(int scanline=cf.height-1;scanline>=0;scanline--,depth+=y_block)
    {
        cout<<"scanline "<<scanline<<endl;
        vector<active_edge> temp;
        for(int i=0;i<edge_active.size();i++)
            {
                active_edge p;
                p=edge_active[i];
                temp.push_back(p);
            }
        edge_active.clear();
        for(int i=0;i<temp.size();i++)
        {
            active_edge p;
            p=temp[i];
            if(p.y_MAX>=depth)
            {
                p.x_intersect+=p.dX*y_block;
                edge_active.push_back(p);
            }
        }
       //// cout<<"SIZE "<<edge_active.size()<<endl;

        for(int i=0;i<edge_map[scanline].size();i++)
        {
            edge t;
            t=edge_map[scanline][i];
            active_edge p;
            p.x_intersect=t.x_at_yMIN;
            p.ID=t.ID;
            p.y_MAX=t.y_MAX;
            p.dX=t.dX;
            edge_active.push_back(p);
        }

      ////  cout<<"SIZE "<<edge_active.size()<<endl;
        std::sort(edge_active.begin(), edge_active.end(), lesser());
        if(edge_active.size()<2)
            cont;

            // vector<active_edge> edge_active;
     //set<ll> polygon_active;
     //set<ll>::iterator it;
     //cout<<edge_active.size()<<endl;

        for(int i=0;i<=edge_active.size()-1;i++)
        {
           active_edge p;
           p=edge_active[i];

           if(i==edge_active.size()-1)
           {
               tri_map[p.ID].bl=false;
                polygon_active.erase(p.ID);
                continue;
           }

           if(tri_map[p.ID].bl==false)
           {
               tri_map[p.ID].bl=true;
               polygon_active.insert(p.ID);
           }
           else
           {
                tri_map[p.ID].bl=false;
                polygon_active.erase(p.ID);
           }

           ////cout<<polygon_active.size()<<" poly"<<endl;


           pair<ll,ll> mypair;
            mypair=x_check(edge_active[i].x_intersect,edge_active[i+1].x_intersect,cf);


            //cout<<"hello "<<mypair.first<<" "<<mypair.second<<endl;
           ll correct_id=which_triangle(depth,left_x+mypair.first*x_block,  cf);
           if( correct_id==-1 || (mypair.first>mypair.second) )
              cont;
            cout<<scanline<<" "<<mypair.first<<" "<<mypair.second<<" "<<correct_id<<endl;
           for(int j=mypair.first;j<=mypair.second;j++)
           {

               image.set_pixel(j, scanline,tri_map[correct_id].color[0] ,  tri_map[correct_id].color[1],    tri_map[correct_id].color[2]);
           }

        }

    }

image.save_image("2.bmp");

delete &image;
edge_active.clear();
polygon_active.clear();
alltriangle.clear();
tri_map.clear();
alledge.clear();
edge_map.clear();



}
