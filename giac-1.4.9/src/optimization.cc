/*
 * optimization.cc
 *
 * Copyright 2017 Luka Marohnić
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * __________________________________________________________________________
 * |Example of using 'extrema', 'minimize' and 'maximize' functions to solve|
 * |the set of exercises found in:                                          |
 * |https://math.feld.cvut.cz/habala/teaching/veci-ma2/ema2r3.pdf           |
 * ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 * 1) Input:
 *        extrema(2x^3+9x*y^2+15x^2+27y^2,[x,y])
 *    Result: we get local minimum at origin, local maximum at (-5,0)
 *            and (-3,2),(-3,-2) as saddle points.
 *
 * 2) Input:
 *        extrema(x^3-2x^2+y^2+z^2-2x*y+x*z-y*z+3z,[x,y,z])
 *    Result: the given function has local minimum at (2,1,-2).
 *
 * 3) Input:
 *        minimize(x^2+2y^2,x^2-2x+2y^2+4y=0,[x,y]);
 *        maximize(x^2+2y^2,x^2-2x+2y^2+4y=0,[x,y])
 *    Result: the minimal value of x^2+2y^2 is 0 and the maximal is 12.
 *
 * 4) We need to minimize f(x,y,z)=x^2+(y+3)^2+(z-2)^2 for points (x,y,z)
 *    lying in plane x+y-z=1. Since the feasible area is not bounded, we're
 *    using the function 'extrema' because obviously the function has single
 *    local minimum.
 *    Input:
 *        extrema(x^2+(y+3)^2+(z-2)^2,x+y-z=1,[x,y,z])
 *    Result: the point closest to P in x+y-z=1 is (2,-1,0), and the distance
 *            is equal to sqrt(f(2,-1,0))=2*sqrt(3).
 *
 * 5) We're using the same method as in exercise 4.
 *    Input:
 *        extrema((x-1)^2+(y-2)^2+(z+1)^2,[x+y+z=1,2x-y+z=3],[x,y,z])
 *    Result: the closest point is (2,0,-1) and the corresponding distance
 *            equals to sqrt(5).
 *
 * 6) First we need to determine the feasible area. Plot its bounds with:
 *        implicitplot(x^2+(y+1)^2-4,x,y);line(y=-1);line(y=x+1)
 *    Now we see that the feasible area is given by set of inequalities:
 *        cond:=[x^2+(y+1)^2<=4,y>=-1,y<=x+1]
 *    Draw this area with:
 *        plotinequation(cond,[x,y],xstep=0.05,ystep=0.05)
 *    Now calculate global minimum and maximum of f(x,y)=x^2+4y^2 on that area:
 *        f(x,y):=x^2+4y^2;
 *        minimize(f(x,y),cond,[x,y]);maximize(f(x,y),cond,[x,y])
 *    Result: the minimum is 0 and the maximum is 8.
 *
 * 7) Input:
 *        minimize(x^2+y^2-6x+6y,x^2+y^2<=4,[x,y]);
 *        maximize(x^2+y^2-6x+6y,x^2+y^2<=4,[x,y])
 *    Result: the minimum is 4-12*sqrt(2) and the maximum is 4+12*sqrt(2).
 *
 * 8) Input:
 *        extrema(y,y^2+2x*y=2x-4x^2,[x,y])
 *    Result: we obtain (1/2,-1) as local minimum and (1/6,1/3) as local
 *            maximum of f(x,y)=y. Therefore, the maximal value is y(1/2)=-1
 *            and the maximal value is y(1/6)=1/3.
 *
 * The above set of exercises could be turned into an example Xcas worksheet.
 */

#include "giacPCH.h"
#include "optimization.h"
#include "giac.h"
#include <sstream>
using namespace std;

using namespace std;

#ifndef NO_NAMESPACE_GIAC
namespace giac {
#endif // ndef NO_NAMESPACE_GIAC

gen make_idnt(const char* name,int index=-1,bool intern=true) {
    stringstream ss;
    if (intern)
        ss << " ";
    ss << string(name);
    if (index>=0)
        ss << index;
    return identificateur(ss.str().c_str());
}

/*
 * Return true iff the expression 'e' is constant with respect to
 * variables in 'vars'.
 */
bool is_constant_wrt_vars(const gen & e,vecteur & vars,GIAC_CONTEXT) {
    for (const_iterateur it=vars.begin();it!=vars.end();++it) {
        if (!is_constant_wrt(e,*it,contextptr))
            return false;
    }
    return true;
}

/*
 * Return true iff the expression 'e' is rational with respect to
 * variables in 'vars'.
 */
bool is_rational_wrt_vars(const gen & e,vecteur & vars,GIAC_CONTEXT) {
    for (const_iterateur it=vars.begin();it!=vars.end();++it) {
        vecteur l(rlvarx(e,*it));
        if (l.size()>1)
            return false;
    }
    return true;
}

/*
 * Solves a system of equations.
 * This function is based on _solve but handles cases where a variable
 * is found inside trigonometric, hyperbolic or exponential functions.
 */
vecteur solve2(vecteur & e_orig,vecteur & vars_orig,GIAC_CONTEXT) {
    int m=e_orig.size(),n=vars_orig.size(),i=0;
    for (;i<m;++i) {
        if (!is_rational_wrt_vars(e_orig[i],vars_orig,contextptr))
            break;
    }
    if (n==1 || i==m)
        return *_solve(makesequence(e_orig,vars_orig),contextptr)._VECTptr;
    vecteur e(*halftan(_texpand(hyp2exp(e_orig,contextptr),contextptr),contextptr)._VECTptr);
    vecteur lv(*exact(lvar(_evalf(lvar(e),contextptr)),contextptr)._VECTptr);
    vecteur deps(n),depvars(n,gen(0));
    vecteur vars(vars_orig);
    const_iterateur it=lv.begin();
    for (;it!=lv.end();++it) {
        i=0;
        for (;i<n;++i) {
            if (is_undef(vars[i]))
                continue;
            if (*it==(deps[i]=vars[i]) ||
                    *it==(deps[i]=exp(vars[i],contextptr)) ||
                    is_zero(_simplify(*it-(deps[i]=tan(vars[i]/gen(2),contextptr)),contextptr))) {
                vars[i]=undef;
                depvars[i]=make_idnt("depvar",i);
                break;
            }
        }
        if (i==n)
            break;
    }
    if (it!=lv.end() || find(depvars.begin(),depvars.end(),gen(0))!=depvars.end())
        return *_solve(makesequence(e_orig,vars_orig),contextptr)._VECTptr;
    vecteur e_subs(subst(e,deps,depvars,false,contextptr));
    vecteur sol(*_solve(makesequence(e_subs,depvars),contextptr)._VECTptr);
    vecteur ret;
    for (const_iterateur it=sol.begin();it!=sol.end();++it) {
        vecteur r(n);
        i=0;
        for (;i<n;++i) {
            gen c(it->_VECTptr->at(i));
            if (deps[i].type==_IDNT)
                r[i]=c;
            else if (deps[i].is_symb_of_sommet(at_exp) && is_strictly_positive(c,contextptr))
                r[i]=_ratnormal(ln(c,contextptr),contextptr);
            else if (deps[i].is_symb_of_sommet(at_tan))
                r[i]=_ratnormal(2*atan(c,contextptr),contextptr);
            else
                break;
        }
        if (i==n)
            ret.push_back(r);
    }
    return ret;
}

/*
 * Traverse the tree of symbolic expression 'e' and collect all points of
 * transition in piecewise subexpressions, no matter of the inequality sign.
 * Nested piecewise expressions are not supported.
 */
void gather_piecewise_transitions(const gen & e,vecteur & cv,GIAC_CONTEXT) {
    if (e.type!=_SYMB)
        return;
    gen & f = e._SYMBptr->feuille;
    if (f.type==_VECT) {
        for (const_iterateur it=f._VECTptr->begin();it!=f._VECTptr->end();++it) {
            if (e.is_symb_of_sommet(at_piecewise) || e.is_symb_of_sommet(at_when)) {
                if (it->is_symb_of_sommet(at_equal) ||
                        it->is_symb_of_sommet(at_different) ||
                        it->is_symb_of_sommet(at_inferieur_egal) ||
                        it->is_symb_of_sommet(at_superieur_egal) ||
                        it->is_symb_of_sommet(at_inferieur_strict) ||
                        it->is_symb_of_sommet(at_superieur_strict)) {
                    vecteur & w = *it->_SYMBptr->feuille._VECTptr;
                    cv.push_back(w[0].type==_IDNT?w[1]:w[0]);
                }
            }
            else {
                gather_piecewise_transitions(*it,cv,contextptr);
            }
        }
    }
    else
        gather_piecewise_transitions(f,cv,contextptr);
}

bool next_binary_perm(vector<bool> & perm,int to_end=0) {
    if (to_end==int(perm.size()))
        return false;
    int end=int(perm.size())-1-to_end;
    perm[end]=!perm[end];
    return perm[end]?true:next_binary_perm(perm,to_end+1);
}

/*
 * Determine critical points of function f under constraints g<=0 and h=0 using
 * Karush-Kuhn-Tucker conditions.
 */
vecteur critical_kkt(gen & f,vecteur & g,vecteur & h,vecteur & vars_orig,GIAC_CONTEXT) {
    int n=vars_orig.size(),m=g.size(),l=h.size();
    vecteur vars(vars_orig),gr_f(*_grad(makesequence(f,vars_orig),contextptr)._VECTptr),mug;
    matrice gr_g,gr_h;
    vars.resize(n+m+l);
    for (int i=0;i<m;++i) {
        vars[n+i]=make_idnt("mu",n+i);
        giac_assume(symb_superieur_strict(vars[n+i],gen(0)),contextptr);
        gr_g.push_back(*_grad(makesequence(g[i],vars_orig),contextptr)._VECTptr);
    }
    for (int i=0;i<l;++i) {
        vars[n+m+i]=make_idnt("lambda",n+m+i);
        gr_h.push_back(*_grad(makesequence(h[i],vars_orig),contextptr)._VECTptr);
    }
    vecteur eqv;
    for (int i=0;i<n;++i) {
        gen eq(gr_f[i]);
        for (int j=0;j<m;++j) {
            eq+=vars[n+j]*gr_g[j][i];
        }
        for (int j=0;j<l;++j) {
            eq+=vars[n+m+j]*gr_h[j][i];
        }
        eqv.push_back(eq);
    }
    eqv=mergevecteur(eqv,h);
    vector<bool> is_mu_zero(m,false);
    matrice cv;
    do {
        vecteur e(eqv);
        vecteur v(vars);
        for (int i=m-1;i>=0;--i) {
            if (is_mu_zero[i]) {
                e=subst(e,v[n+i],gen(0),false,contextptr);
                v.erase(v.begin()+n+i);
            }
            else
                e.push_back(g[i]);
        }
        cv=mergevecteur(cv,solve2(e,v,contextptr));
    } while(next_binary_perm(is_mu_zero));
    vars.resize(n);
    for (int i=cv.size()-1;i>=0;--i) {
        cv[i]._VECTptr->resize(n);
        for (int j=0;j<m;++j) {
            if (is_strictly_positive(subst(g[j],vars,cv[i],false,contextptr),contextptr)) {
                cv.erase(cv.begin()+i);
                break;
            }
        }
    }
    return cv;
}

/*
 * Determine critical points of an univariate function f(x). Points where it is
 * not differentiable are considered critical as well as zeros of the first
 * derivative. Also, bounds of the range of x are critical points.
 */
matrice critical_univariate(gen & f,identificateur & x,GIAC_CONTEXT) {
    gen df(_derive(makesequence(f,x),contextptr));
    matrice cv(*_solve(makesequence(symb_equal(df,gen(0)),x),contextptr)._VECTptr);
    vecteur range;
    find_range(x,range,contextptr);
    range=*range[0]._VECTptr;
    if (!is_inf(-range[0]))
        cv.push_back(range[0]);
    if (!is_inf(range[1]))
        cv.push_back(range[1]);
    gen den(_denom(df,contextptr));
    if (!is_constant_wrt(den,x,contextptr)) {
        cv=mergevecteur(cv,*_solve(makesequence(symb_equal(den,gen(0)),x),contextptr)._VECTptr);
    }
    gather_piecewise_transitions(f,cv,contextptr);  // assuming that f is not differentiable on transitions
    for (int i=cv.size()-1;i>=0;--i) {
        if (cv[i].is_symb_of_sommet(at_and))
            cv.erase(cv.begin()+i);
        else
            cv[i]=vecteur(1,cv[i]);
    }
    return cv;
}

/*
 * Compute global minimum mn and global maximum mx of function f(vars) under
 * conditions g<=0 and h=0. The list of points where global minimum is achieved
 * is returned.
 */
vecteur global_extrema(gen & f,vecteur & g,vecteur & h,vecteur & vars,gen & mn,gen & mx,GIAC_CONTEXT) {
    int n=vars.size();
    matrice cv(n==1?critical_univariate(f,*vars[0]._IDNTptr,contextptr):critical_kkt(f,g,h,vars,contextptr));
    if (cv.empty())
        return vecteur(0);
    bool min_set=false,max_set=false;
    matrice min_locations;
    for (const_iterateur it=cv.begin();it!=cv.end();++it) {
        gen val(subst(f,vars,*it,false,contextptr));
        if (min_set && is_exactly_zero(val-mn)) {
            if (find(min_locations.begin(),min_locations.end(),*it)==min_locations.end())
                min_locations.push_back(*it);
        }
        else if (!min_set || is_greater(mn,val,contextptr)) {
            mn=val;
            min_set=true;
            min_locations=vecteur(1,*it);
        }
        if (!max_set || is_strictly_greater(val,mx,contextptr)) {
            mx=val;
            max_set=true;
        }
    }
    if (n==1) {
        for (int i=0;i<int(min_locations.size());++i) {
            min_locations[i]=min_locations[i][0];
        }
    }
    return min_locations;
}

vecteur parse_varlist(vecteur & gv, int ngv,vecteur & vars,vecteur & initial,GIAC_CONTEXT) {
    vecteur varlist(gv[ngv-1].type==_VECT ? *gv[ngv-1]._VECTptr : vecteur(1,gv[ngv-1]));
    int n=varlist.size();
    vars=vecteur(n);
    vecteur range,oldvars(n);
    for (int i=0;i<n;++i) {
        gen & v = varlist[i];
        range.clear();
        vars[i]=make_idnt("x",i);
        purgenoassume(vars[i],contextptr);
        if (v.is_symb_of_sommet(at_equal)) {
            vecteur & ops = *v._SYMBptr->feuille._VECTptr;
            if (ops[0].type!=_IDNT)
                return 0;
            oldvars[i]=ops[0];
            if (ops[1].is_symb_of_sommet(at_interval)) {
                // variable is required to be in range specified by ops[1]
                range=*ops[1]._SYMBptr->feuille._VECTptr;
                bool has_lower=!is_inf(-range[0]),has_upper=!is_inf(range[1]);
                if (has_lower && has_upper)
                    assume_t_in_ab(vars[i],range[0],range[1],true,true,contextptr);
                else if (has_lower)
                    giac_assume(symb_superieur_strict(vars[i],range[0]),contextptr);
                else if (has_upper)
                    giac_assume(symb_inferieur_strict(vars[i],range[1]),contextptr);
            }
            else
                initial.push_back(ops[1]);
        }
        else if (v.type!=_IDNT)
            return 0;
        else
            oldvars[i]=v;
    }
    // return detected variables
    return oldvars;
}

/*
 * Function 'minimize' minimizes a multivariate continuous function on a
 * closed and bounded region using the method of Lagrange multipliers. The
 * feasible region is specified by bounding variables or by adding one or
 * more (in)equality constraints.
 *
 * Usage
 * ^^^^^
 *     minimize(obj,[constr],vars,[opt])
 *
 * Parameters
 * ^^^^^^^^^^
 *   - obj                 : objective function to minimize
 *   - constr (optional)   : single equality or inequality constraint or
 *                           a list of constraints, if constraint is given as
 *                           expression it is assumed that it is equal to zero
 *   - vars                : single variable or a list of problem variables, where
 *                           optional bounds of a variable may be set by appending '=a..b'
 *   - location (optional) : the option keyword 'locus' or 'coordinates' or 'point'
 *
 * Objective function must be continuous in all points of the feasible region,
 * which is assumed to be closed and bounded. If one of these condinitions is
 * not met, the final result may be incorrect.
 *
 * When the fourth argument is specified, point(s) at which the objective
 * function attains its minimum value are also returned as a list of vector(s).
 * The keywords 'locus', 'coordinates' and 'point' all have the same effect.
 * For univariate problems, a vector of numbers (x values) is returned, while
 * for multivariate problems it is a vector of vectors, i.e. a matrix.
 *
 * The function attempts to obtain the critical points in exact form, if the
 * parameters of the problem are all exact. It works best for problems in which
 * the lagrangian function gradient consists of rational expressions. Points at
 * which the function is not differentiable are also considered critical. This
 * function also handles univariate piecewise functions.
 *
 * If no critical points were obtained, the return value is undefined.
 *
 * Examples
 * ^^^^^^^^
 * minimize(sin(x),[x=0..4])
 *    >> sin(4)
 * minimize(asin(x),x=-1..1)
 *    >> -pi/2
 * minimize(x^2+cos(x),x=0..3)
 *    >> 1
 * minimize(x^4-x^2,x=-3..3,locus)
 *    >> -1/4,[-sqrt(2)/2]
 * minimize(abs(x),x=-1..1)
 *    >> 0
 * minimize(x-abs(x),x=-1..1)
 *    >> -2
 * minimize(abs(exp(-x^2)-1/2),x=-4..4)
 *    >> 0
 * minimize(piecewise(x<=-2,x+6,x<=1,x^2,3/2-x/2),x=-3..2)
 *    >> 0
 * minimize(x^2-3x+y^2+3y+3,[x=2..4,y=-4..-2],point)
 *    >> -1,[[2,-2]]
 * minimize(2x^2+y^2,x+y=1,[x,y])
 *    >> 2/3
 * minimize(2x^2-y^2+6y,x^2+y^2<=16,[x,y])
 *    >> -40
 * minimize(x*y+9-x^2-y^2,x^2+y^2<=9,[x,y])
 *    >> -9/2
 * minimize(sqrt(x^2+y^2)-z,[x^2+y^2<=16,x+y+z=10],[x,y,z])
 *    >> -4*sqrt(2)-6
 * minimize(x*y*z,x^2+y^2+z^2=1,[x,y,z])
 *    >> -sqrt(3)/9
 * minimize(sin(x)+cos(x),x=0..20,coordinates)
 *    >> -sqrt(2),[5*pi/4,13*pi/4,21*pi/4]
 * minimize((1+x^2+3y+5x-4*x*y)/(1+x^2+y^2),x^2/4+y^2/3=9,[x,y])
 *    >> -2.44662490691
 * minimize(x^2-2x+y^2+1,[x+y<=0,x^2<=4],[x,y],locus)
 *    >> 1/2,[[1/2,-1/2]]
 * minimize(x^2*(y+1)-2y,[y<=2,sqrt(1+x^2)<=y],[x,y])
 *    >> -4
 * minimize(4x^2+y^2-2x-4y+1,4x^2+y^2=1,[x,y])
 *    >> -sqrt(17)+2
 * minimize(cos(x)^2+cos(y)^2,x+y=pi/4,[x,y],locus)
 *    >> (-sqrt(2)+2)/2,[[5*pi/8,-3*pi/8]]
 * minimize(x^2+y^2,x^4+y^4=2,[x,y])
 *    >> 1.41421356237
 * minimize(z*x*exp(y),z^2+x^2+exp(2y)=1,[x,y,z])
 *    >> -sqrt(3)/9
 */
gen _minimize(const gen & args,GIAC_CONTEXT) {
    if (args.type==_STRNG && args.subtype==-1) return args;
    if (args.type!=_VECT || args.subtype!=_SEQ__VECT || args._VECTptr->size()>4)
        return gentypeerr(contextptr);
    vecteur & argv = *args._VECTptr,g,h;
    bool location=false;
    int nargs=argv.size();
    if (argv.back()==at_coordonnees || argv.back()==at_lieu || argv.back()==at_point) {
        location=true;
        --nargs;
    }
    if (nargs==3) {
        vecteur constr(argv[1].type==_VECT ? *argv[1]._VECTptr : vecteur(1,argv[1]));
        for (const_iterateur it=constr.begin();it!=constr.end();++it) {
            if ((*it).is_symb_of_sommet(at_equal))
                h.push_back(equal2diff(*it));
            else if ((*it).is_symb_of_sommet(at_superieur_egal) ||
                     (*it).is_symb_of_sommet(at_inferieur_egal))
                g.push_back(*it);
            else
                h.push_back(*it);
        }
    }
    vecteur vars,oldvars,initial;
    int n;  // number of variables
    if ((n=(oldvars=parse_varlist(argv,nargs,vars,initial,contextptr)).size())==0 || !initial.empty())
        return gensizeerr(contextptr);
    for (int i=0;i<int(g.size());++i) {
        gen & gi = g[i];
        vecteur & s = *gi._SYMBptr->feuille._VECTptr;
        g[i]=gi.is_symb_of_sommet(at_inferieur_egal)?s[0]-s[1]:s[1]-s[0];
    }
    vecteur range;
    for (const_iterateur it=vars.begin();it!=vars.end();++it) {
        find_range(*it,range,contextptr);
        range=*range[0]._VECTptr;
        if (!is_inf(-range[0]))
            g.push_back(range[0]-*it);
        if (!is_inf(range[1]))
            g.push_back(*it-range[1]);
        if (n>1)
            purgenoassume(*it,contextptr);
    }
    gen f(subst(argv[0],oldvars,vars,false,contextptr));
    g=subst(g,oldvars,vars,false,contextptr);
    h=subst(h,oldvars,vars,false,contextptr);
    gen mn,mx;
    vecteur loc(global_extrema(f,g,h,vars,mn,mx,contextptr));
    if (loc.empty())
        return undef;
    if (location)
        return makesequence(_simplify(mn,contextptr),_simplify(loc,contextptr));
    return _simplify(mn,contextptr);
}
static const char _minimize_s []="minimize";
static define_unary_function_eval (__minimize,&_minimize,_minimize_s);
define_unary_function_ptr5(at_minimize,alias_at_minimize,&__minimize,0,true)

/*
 * 'maximize' takes the same arguments as the function 'minimize', but
 * maximizes the objective function. See 'minimize' for details.
 *
 * Examples
 * ^^^^^^^^
 * maximize(cos(x),x=1..3)
 *    >> cos(1)
 * maximize(piecewise(x<=-2,x+6,x<=1,x^2,3/2-x/2),x=-3..2)
 *    >> 4
 * minimize(x-abs(x),x=-1..1)
 *    >> 0
 * maximize(x^2-3x+y^2+3y+3,[x=2..4,y=-4..-2])
 *    >> 11
 * maximize(x*y*z,x^2+2*y^2+3*z^2<=1,[x,y,z],point)
 *    >> sqrt(2)/18,[[-sqrt(3)/3,sqrt(6)/6,-1/3],[sqrt(3)/3,-sqrt(6)/6,-1/3],
 *                   [-sqrt(3)/3,-sqrt(6)/6,1/3],[sqrt(3)/3,sqrt(6)/6,1/3]]
 * maximize(x^2-x*y+2*y^2,[x=-1..0,y=-1/2..1/2],coordinates)
 *    >> 2,[[-1,1/2]]
 * maximize(x*y,[x+y^2<=2,x>=0,y>=0],[x,y],locus)
 *    >> 4*sqrt(6)/9,[[4/3,sqrt(6)/3]]
 * maximize(y^2-x^2*y,y<=x,[x=0..2,y=0..2])
 *    >> 4/27
 * maximize(2x+y,4x^2+y^2=8,[x,y])
 *    >> 4
 * maximize(x^2*(y+1)-2y,[y<=2,sqrt(1+x^2)<=y],[x,y])
 *    >> 5
 * maximize(4x^2+y^2-2x-4y+1,4x^2+y^2=1,[x,y])
 *    >> sqrt(17)+2
 * maximize(3x+2y,2x^2+3y^2<=3,[x,y])
 *    >> sqrt(70)/2
 * maximize(x*y,[2x+3y<=10,x>=0,y>=0],[x,y])
 *    >> 25/6
 * maximize(x^2+y^2+z^2,[x^2/16+y^2+z^2=1,x+y+z=0],[x,y,z])
 *    >> 8/3
 * assume(a>0);maximize(x^2*y^2*z^2,x^2+y^2+z^2=a^2,[x,y,z])
 *    >> a^6/27
 */
gen _maximize(const gen & g,GIAC_CONTEXT) {
    if (g.type==_STRNG && g.subtype==-1) return g;
    if (g.type!=_VECT || g.subtype!=_SEQ__VECT || g._VECTptr->size()<2)
        return gentypeerr(contextptr);
    vecteur gv(*g._VECTptr);
    gv[0]=-gv[0];
    gen res=_minimize(_feuille(gv,contextptr),contextptr);
    if (res.type==_VECT && res._VECTptr->size()>0) {
        res._VECTptr->front()=-res._VECTptr->front();
    }
    else if (res.type!=_VECT)
        res=-res;
    return res;
}
static const char _maximize_s []="maximize";
static define_unary_function_eval (__maximize,&_maximize,_maximize_s);
define_unary_function_ptr5(at_maximize,alias_at_maximize,&__maximize,0,true)

/*
 * Partition nonnegative integer m into n nonnegative integers x1,x2,...,xn. All
 * possible combinations are put in c.
 */
void partition_m_in_n_terms (int m,int n,vector<vint> & c,vint p=vint(0)) {
    if (p.empty())
        p=vint(n,0);
    for (int i=0;i<n;++i) {
        if (p[i]!=0)
            continue;
        vint r(p);
        for (int j=0;j<m;++j) {
            ++r[i];
            int s=0;
            for (vint::const_iterator it=r.begin();it!=r.end();++it) {
                s+=*it;
            }
            if (s==m && find(c.begin(),c.end(),r)==c.end())
                c.push_back(r);
            else if (s<m)
                partition_m_in_n_terms(m,n,c,r);
            else break;
        }
    }
}

int sum_vint(vint & v,bool drop_last=false) {
    int s=0;
    for (vint::const_iterator it=v.begin();it!=v.end()-drop_last?1:0;++it) {
        s+=*it;
    }
    return s;
}

/*
void print_t(diffterm t) {
    cout << "f: " << t.first << endl;
    cout << "h: ";
    for (map<vint,int>::const_iterator it=t.second.begin();it!=t.second.end();++it) {
        cout << it->first << "^" << it->second << " ";
    }
    cout << endl;
}
*/

impldiff derive_diffterms(impldiff & terms,int n,int m,vint & sig) {
    while (!sig.empty() && sig.back()==0) {
        sig.pop_back();
    }
    if (sig.empty())
        return terms;
    int k=int(sig.size())-1;
    impldiff tv;
    for (impldiff::const_iterator it=terms.begin();it!=terms.end();++it) {
        int c=it->second;
        diffterm t(it->first);
        map<vint,int> h_orig(it->first.second);
        ++t.first.at(k);
        tv[t]+=c;
        --t.first.at(k);
        map<vint,int> h(h_orig);
        for (map<vint,int>::const_iterator jt=h_orig.begin();jt!=h_orig.end();++jt) {
            vint v(jt->first);
            int p(jt->second);
            if (p==0)
                continue;
            if (p==1)
                h.erase(h.find(v));
            else
                --h[v];
            ++v[k];
            ++h[v];
            t.second=h;
            tv[t]+=c*p;
            --h[v];
            --v[k];
            ++h[v];
        }
        t.second=h_orig;
        for (int i=0;i<m;++i) {
            ++t.first.at(n+i);
            vint u(n,0);
            u[k]=1;
            u.push_back(i);
            ++t.second[u];
            tv[t]+=c;
            --t.first.at(n+i);
            --t.second[u];
        }
    }
    --sig.back();
    return derive_diffterms(tv,n,m,sig);
}

gen get_pd(map<vint,gen> & pdv,const vint & sig) {
    gen ret;
#ifndef NO_STDEXCEPT
    try {
#endif
        ret=pdv.at(sig);
#ifndef NO_STDEXCEPT
    }
    catch (out_of_range & e) {
        ret=undef;
    }
#endif
    return ret;
}

gen compute_pd(gen & f,vecteur & vars,map<vint,gen> & pdv,vint & sig,GIAC_CONTEXT) {
    gen pd(get_pd(pdv,sig));
    if (!is_undef(pd))
        return pd;
    vecteur v(1,f);
    bool do_derive=false;
    assert(vars.size()<=sig.size());
    for (int i=0;i<int(vars.size());++i) {
        if (sig[i]>0) {
            v=mergevecteur(v,vecteur(sig[i],vars[i]));
            do_derive=true;
        }
    }
    if (do_derive)
        return pdv[sig]=_derive(_feuille(v,contextptr),contextptr);
    return f;
}

void compute_h(vecteur & g,vecteur & vars,vector<impldiff> & grv,
               map<vint,gen> & pdg,map<vint,gen> & pdh,int order,GIAC_CONTEXT) {
    if (g.empty())
        return;
    vector<vint> hsigv;
    matrice A;
    vecteur b(g.size()*grv.size(),gen(0));
    for (int i=0;i<int(g.size());++i) {
        for (int j=0;j<int(grv.size());++j) {
            vecteur eq(g.size()*grv.size(),gen(0));
            for (impldiff::const_iterator it=grv[j].begin();it!=grv[j].end();++it) {
                vint sig(it->first.first),hsig;
                int cf=it->second;
                sig.push_back(i);
                gen t(gen(cf)*compute_pd(g[i],vars,pdg,sig,contextptr));
                for (map<vint,int>::const_iterator ht=it->first.second.begin();ht!=it->first.second.end();++ht) {
                    if (ht->second==0)
                        continue;
                    sig=ht->first;
                    if (sum_vint(sig,true)<order) {
                        gen h(get_pd(pdh,sig));
                        assert(!is_undef(h));
                        t=t*pow(h,ht->second);
                    }
                    else {
                        assert(ht->second==1);
                        hsig=sig;
                    }
                }
                if (hsig.empty())
                    b[grv.size()*i+j]-=t;
                else {
                    int k=0;
                    for (;k<int(hsigv.size());++k) {
                        if (hsigv[k]==hsig)
                            break;
                    }
                    eq[k]+=t;
                    if (k==int(hsigv.size()))
                        hsigv.push_back(hsig);
                }
            }
            A.push_back(*_ratnormal(eq,contextptr)._VECTptr);
        }
    }
    matrice B;
    B.push_back(*_ratnormal(b,contextptr)._VECTptr);
    matrice invA=*_inv(A,contextptr)._VECTptr;
    vecteur sol(*mtran(mmult(invA,mtran(B))).front()._VECTptr);
    for (int i=0;i<int(sol.size());++i) {
        pdh[hsigv[i]]=sol[i];
    }
}

void find_nearest_terms(const map<vint,impldiff> & terms,vint & sig,impldiff & match,vint & excess) {
    int n=sig.size();
    excess=sig;
    for (map<vint,impldiff>::const_iterator it=terms.begin();it!=terms.end();++it) {
        vint ex(n,0);
        int i=0;
        for (;i<n;++i) {
            if ((ex[i]=sig[i]-it->first.at(i))<0)
                break;
        }
        if (i<n)
            continue;
        if (sum_vint(ex)<sum_vint(excess)) {
            excess=ex;
            match=it->second;
        }
    }
}

map<vint,gen> implicit_partial_derivatives(
        gen & f,vecteur & g,vecteur & vars,int order,vint sig,map<vint,impldiff> & cterms,
        map<vint,gen> & pdf,map<vint,gen> & pdg,GIAC_CONTEXT) {
    int m=g.size();
    int n=vars.size()-m;
    map<vint,gen> pdh,pdv;
    pdv[vint(n,0)]=f;
    if (order==0)
        return pdv;
    vector<vint> c;
    vint excess,init_f(n+m,0);
    diffterm init_term;
    init_term.first=init_f;
    impldiff init_terms;
    init_terms[init_term]=1;
    vector<impldiff> grv;
    for (int k=1;k<=order;++k) {
        grv.clear();
        c.clear();
        partition_m_in_n_terms(k,n,c);
        for (vector<vint>::iterator it=c.begin();it!=c.end();++it) {
            impldiff terms=init_terms;
            find_nearest_terms(cterms,*it,terms,excess);
            if (sum_vint(excess)>0) {
                terms=derive_diffterms(terms,n,m,excess);
                cterms[*it]=terms;
            }
            grv.push_back(terms);
        }
        compute_h(g,vars,grv,pdg,pdh,k,contextptr);
    }
    gen pd;
    for (vector<vint>::const_iterator ct=c.begin();ct!=c.end();++ct) {
        if (!sig.empty() && sig!=*ct)
            continue;
        impldiff & terms=cterms[*ct];
        pd=gen(0);
        for (impldiff::const_iterator it=terms.begin();it!=terms.end();++it) {
            vint sig(it->first.first);
            int cf=it->second;
            gen t(gen(cf)*compute_pd(f,vars,pdf,sig,contextptr));
            if (!is_zero(t)) {
                for (map<vint,int>::const_iterator jt=it->first.second.begin();jt!=it->first.second.end();++jt) {
                    if (jt->second==0)
                        continue;
                    gen h(get_pd(pdh,jt->first));
                    assert(!is_undef(h));
                    t=t*pow(h,jt->second);
                }
                pd+=t;
            }
        }
        pdv[*ct]=_ratnormal(pd,contextptr);
    }
    return pdv;
}

vint rearrange_vars(matrice J,GIAC_CONTEXT) {
    vint v;
    int m=J.size();
    matrice tJ(mtran(J));
    for (int i=0;i<int(tJ.size());++i) {
        v.push_back(i);
    }
    do {
        matrice S;
        for (vint::const_iterator it=v.end()-m;it!=v.end();++it) {
            S.push_back(tJ[*it]);
        }
        if (!is_zero(_det(S,contextptr)))
            break;
    } while (next_permutation(v.begin(),v.end()));
    return v;
}

matrice jacobian(vecteur & g,vecteur & vars,GIAC_CONTEXT) {
    matrice J;
    for (int i=0;i<int(g.size());++i) {
        J.push_back(*_grad(makesequence(g[i],vars),contextptr)._VECTptr);
    }
    return J;
}

bool ck_jacobian(vecteur & g,vecteur & vars,GIAC_CONTEXT) {
    matrice J(jacobian(g,vars,contextptr));
    int m=g.size();
    int n=vars.size()-m;
    if (_rank(J,contextptr).val<m)
        return false;
    J=mtran(J);
    J.erase(J.begin(),J.begin()+n);
    if (is_zero(_det(J,contextptr)))
        return false;
    return true;
}

vecteur pdv2gradient(map<vint,gen> pdv,int n) {
    vecteur gr;
    for (int i=0;i<n;++i) {
        vint sig(n,0);
        sig[i]=1;
        gr.push_back(pdv[sig]);
    }
    return gr;
}

matrice pdv2hessian(map<vint,gen> pdv,int n) {
    matrice hess;
    for (int i=0;i<n;++i) {
        vecteur r(n);
        for (int j=0;j<n;++j) {
            vint sig(n,0);
            ++sig[i];
            ++sig[j];
            r[j]=pdv[sig];
        }
        hess.push_back(r);
    }
    return hess;
}

/*
 * 'implicitdiff' differentiates function(s) defined by equation(s) or a
 * function f(x1,x2,...,xn,y1,y2,...,ym) where y1,...,ym are functions of
 * x1,x2,...,xn defined by m equality constraints.
 *
 * Usage
 * ^^^^^
 *      implicitdiff(f,constr,depvars,diffvars)
 *      implicitdiff(f,constr,vars,order_size=<posint>,[P])
 *      implicitdiff(constr,[depvars],y,diffvars)
 *
 * Parameters
 * ^^^^^^^^^^
 *      - f         : expression
 *      - constr    : (list of) equation(s)
 *      - depvars   : (list of) dependent variable(s), each of them given
 *                    either as a symbol, e.g. y, or a function, e.g. y(x,z)
 *      - diffvars  : sequence of variables w.r.t. which the differentiation
 *                    will be carried out
 *      - vars      : list all variables on which f depends such that
 *                  : dependent variables come after independent ones
 *      - P         : (list of) coordinate(s) to compute derivatives at
 *      - y         : (list of) dependent variable(s) to differentiate w.r.t.
 *                    diffvars, each of them given as a symbol
 *
 * The return value is partial derivative specified by diffvars. If
 * 'order_size=m' is given as the fourth argument, all partial derivatives of
 * order m will be computed and returned as vector for m=1, matrix for m=2 or
 * table for m>2. The first two cases produce gradient and hessian of f,
 * respectively. For m>2, the partial derivative
 * pd=d^m(f)/(d^k1(x1)*d^k2(x2)*...*d^kn(xn)) is saved under key [k1,k2,...kn].
 * If P is specified, pd(P) is saved.
 *
 * Examples
 * ^^^^^^^^
 * implicitdiff(x^2*y+y^2=1,y,x)
 *      >> -2*x*y/(x^2+2*y)
 * implicitdiff(R=P*V/T,P,T)
 *      >> P/T
 * implicitdiff([x^2+y=z,x+y*z=1],[y(x),z(x)],y,x)
 *      >> (-2*x*y-1)/(y+z)
 * implicitdiff([x^2+y=z,x+y*z=1],[y(x),z(x)],[y,z],x)
 *      >> [(-2*x*y-1)/(y+z),(2*x*z-1)/(y+z)]
 * implicitdiff(y=x^2/z,y,x)
 *      >> 2x/z
 * implicitdiff(y=x^2/z,y,z)
 *      >> -x^2/z^2
 * implicitdiff(y^3+x^2=1,y,x)
 *      >> -2*x/(3*y^2)
 * implicitdiff(y^3+x^2=1,y,x,x)
 *      >> (-8*x^2-6*y^3)/(9*y^5)
 * implicitdiff(a*x^3*y-2y/z=z^2,y(x,z),x)
 *      >> -3*a*x^2*y*z/(a*x^3*z-2)
 * implicitdiff(a*x^3*y-2y/z=z^2,y(x,z),x,z)
 *      >> (12*a*x^2*y-6*a*x^2*z^3)/(a^2*x^6*z^2-4*a*x^3*z+4)
 * implicitdiff([-2x*z+y^2=1,x^2-exp(x*z)=y],[y(x),z(x)],y,x)
 *      >> 2*x/(y*exp(x*z)+1)
 * implicitdiff([-2x*z+y^2=1,x^2-exp(x*z)=y],[y(x),z(x)],[y,z],x)
 *      >> [2*x/(y*exp(x*z)+1),(2*x*y-y*z*exp(x*z)-z)/(x*y*exp(x*z)+x)]
 * implicitdiff([a*sin(u*v)+b*cos(w*x)=c,u+v+w+x=z,u*v+w*x=z],[u(x,z),v(x,z),w(x,z)],u,z)
 *      >> (a*u*x*cos(u*v)-a*u*cos(u*v)+b*u*x*sin(w*x)-b*x*sin(w*x))/
 *         (a*u*x*cos(u*v)-a*v*x*cos(u*v)+b*u*x*sin(w*x)-b*v*x*sin(w*x))
 * implicitdiff(x*y,-2x^3+15x^2*y+11y^3-24y=0,y(x),x$2)
 *      >> (162*x^5*y+1320*x^4*y^2-320*x^4-3300*x^3*y^3+800*x^3*y+968*x^2*y^4-1408*x^2*y^2+
 *          512*x^2-3630*x*y^5+5280*x*y^3-1920*x*y)/(125*x^6+825*x^4*y^2-600*x^4+
 *          1815*x^2*y^4-2640*x^2*y^2+960*x^2+1331*y^6-2904*y^4+2112*y^2-512)
 * implicitdiff((x-u)^2+(y-v)^2,[x^2/4+y^2/9=1,(u-3)^2+(v+5)^2=1],[v(u,x),y(u,x)],u,x)
 *      >> (-9*u*x-4*v*y+27*x-20*y)/(2*v*y+10*y)
 * implicitdiff(x*y*z,-2x^3+15x^2*y+11y^3-24y=0,[x,z,y],order_size=1)
 *      >> [(2*x^3*z-5*x^2*y*z+11*y^3*z-8*y*z)/(5*x^2+11*y^2-8),x*y]
 * implicitdiff(x*y*z,-2x^3+15x^2*y+11y^3-24y=0,[x,z,y],order_size=2,[1,-1,0])
 *      >> [[64/9,-2/3],[-2/3,0]]
 * pd:=implicitdiff(x*y*z,-2x^3+15x^2*y+11y^3-24y=0,[x,z,y],order_size=4,[0,z,0]);pd[4,0,0]
 *      >> -2*z
 */
gen _implicitdiff(const gen & g,GIAC_CONTEXT) {
    if (g.type==_STRNG && g.subtype==-1) return g;
    if (g.type!=_VECT || g.subtype!=_SEQ__VECT || g._VECTptr->size()<2)
        return gentypeerr(contextptr);
    vecteur & gv = *g._VECTptr;
    gen & f = gv[0];
    if (int(gv.size())<3)
        return gensizeerr(contextptr);
    int ci=gv[0].type!=_VECT && !gv[0].is_symb_of_sommet(at_equal)?1:0;
    vecteur freevars,depvars,diffdepvars;
    gen_map diffvars;
    // get the constraints as a list of vanishing expressions
    vecteur constr(gv[ci].type==_VECT?*gv[ci]._VECTptr:vecteur(1,gv[ci]));
    for (int i=0;i<int(constr.size());++i) {
        if (constr[i].is_symb_of_sommet(at_equal))
            constr[i]=equal2diff(constr[i]);
    }
    int m=constr.size();
    int dvi=3;
    if (ci==0) {
        if (gv[ci+1].type==_VECT)
            diffdepvars=gv[ci+2].type==_VECT?*gv[ci+2]._VECTptr:vecteur(1,gv[ci+2]);
        else
            dvi=2;
    }
    bool compute_all=false;
    int order=0;
    if (ci==1 && gv[dvi].is_symb_of_sommet(at_equal)) {
        vecteur & v = *gv[dvi]._SYMBptr->feuille._VECTptr;
        if (v.front()!=at_order_size || !v.back().is_integer())
            return gentypeerr(contextptr);
        order=v.back().val;
        if (order<=0)
            return gendimerr(contextptr);
        compute_all=true;
    }
    // get dependency specification
    vecteur deplist(gv[ci+1].type==_VECT?*gv[ci+1]._VECTptr:vecteur(1,gv[ci+1]));
    if (compute_all) {
        // vars must be specified as x1,x2,...,xn,y1,y2,...,ym
        int nd=deplist.size();
        if (nd<=m)
            return gensizeerr(contextptr);
        for (int i=0;i<nd;++i) {
            if (i<nd-m)
                freevars.push_back(deplist[i]);
            else
                depvars.push_back(deplist[i]);
        }
    }
    else {
        // get (in)dependent variables
        for (const_iterateur it=deplist.begin();it!=deplist.end();++it) {
            if (it->type==_IDNT)
                depvars.push_back(*it);
            else if (it->is_symb_of_sommet(at_of)) {
                vecteur fe(*it->_SYMBptr->feuille._VECTptr);
                depvars.push_back(fe.front());
                if (fe.back().type==_VECT) {
                    for (int i=0;i<int(fe.back()._VECTptr->size());++i) {
                        gen & x = fe.back()._VECTptr->at(i);
                        if (find(freevars.begin(),freevars.end(),x)==freevars.end())
                            freevars.push_back(x);
                    }
                }
                else
                    freevars.push_back(fe.back());
            }
            else
                return gentypeerr(contextptr);
        }
        // get diffvars
        for (const_iterateur it=gv.begin()+dvi;it!=gv.end();++it) {
            gen v(eval(*it,contextptr));
            gen x;
            if (v.type==_IDNT)
                diffvars[(x=v)]+=1;
            else if (v.type==_VECT && v.subtype==_SEQ__VECT)
                diffvars[(x=v._VECTptr->front())]+=v._VECTptr->size();
            else
                return gentypeerr(contextptr);
            if (find(freevars.begin(),freevars.end(),x)==freevars.end())
                freevars.push_back(x);
        }
    }
    int n=freevars.size();  // number of independent variables
    if (m!=int(depvars.size()))
        return gensizeerr(contextptr);
    vecteur vars(mergevecteur(freevars,depvars));  // list of all variables
    // check whether the conditions of implicit function theorem hold
    if (!ck_jacobian(constr,vars,contextptr))
        return gendimerr(contextptr);
    // build partial derivative specification 'sig'
    vint sig(n,0); // sig[i]=k means: derive k times with respect to ith independent variable
    map<vint,impldiff> cterms;
    map<vint,gen> pdf,pdg;
    if (compute_all) {
        vecteur pt;
        if (int(gv.size())>4) {
            pt=gv[4].type==_VECT?*gv[4]._VECTptr:vecteur(1,gv[4]);
            if (int(pt.size())!=n+m)
                return gensizeerr(contextptr);
        }
        map<vint,gen> pdv=implicit_partial_derivatives(f,constr,vars,order,vint(0),cterms,pdf,pdg,contextptr);
        if (order==1) {
            vecteur gr(pdv2gradient(pdv,n));
            return pt.empty()?gr:_ratnormal(subst(gr,vars,pt,false,contextptr),contextptr);
        }
        else if (order==2) {
            matrice hess(pdv2hessian(pdv,n));
            return pt.empty()?hess:_ratnormal(subst(hess,vars,pt,false,contextptr),contextptr);
        }
        else {
            vector<vint> c;
            partition_m_in_n_terms(order,n,c);
            gen_map ret_pdv;
            for (vector<vint>::const_iterator it=c.begin();it!=c.end();++it) {
                vecteur v;
                for (int i=0;i<n;++i) {
                    v.push_back(gen(it->at(i)));
                }
                ret_pdv[v]=pt.empty()?pdv[*it]:_ratnormal(subst(pdv[*it],vars,pt,false,contextptr),contextptr);
            }
            return ret_pdv;
        }
    }
    for (gen_map::const_iterator it=diffvars.begin();it!=diffvars.end();++it) {
        int i=0;
        for (;i<n;++i) {
            if (it->first==freevars[i]) {
                sig[i]=it->second.val;
                break;
            }
        }
        assert(i<n);
    }
    // compute the partial derivative specified by 'sig'
    order=sum_vint(sig);
    if (ci==1) {
        map<vint,gen> pdv=implicit_partial_derivatives(f,constr,vars,order,sig,cterms,pdf,pdg,contextptr);
        return _ratnormal(pdv[sig],contextptr);
    }
    vecteur ret;
    if (diffdepvars.empty()) {
        assert(m==1);
        diffdepvars=vecteur(1,depvars.front());
    }
    for (const_iterateur it=diffdepvars.begin();it!=diffdepvars.end();++it) {
        if (find(depvars.begin(),depvars.end(),*it)==depvars.end()) {
            // variable *it is not in depvars, so it's treated as a constant
            ret.push_back(gen(0));
            continue;
        }
        gen fit(*it);
        pdf.clear();
        map<vint,gen> pdv=implicit_partial_derivatives(fit,constr,vars,order,sig,cterms,pdf,pdg,contextptr);
        ret.push_back(_ratnormal(pdv[sig],contextptr));
    }
    return ret.size()==1?ret.front():ret;
}
static const char _implicitdiff_s []="implicitdiff";
static define_unary_function_eval (__implicitdiff,&_implicitdiff,_implicitdiff_s);
define_unary_function_ptr5(at_implicitdiff,alias_at_implicitdiff,&__implicitdiff,0,true)

/*
 * Return kth term of Taylor series for the multivariate function f under
 * condition g=0 in the neighborhood of a. This function uses the multinomial
 * formula to compute 1/k!*(sum(i=1)^n (xi-ai)*d/dxi)^k f(x)|a.
 */
gen compute_implicit_taylor_term(gen & f,vecteur & g,vecteur & a,vecteur & vars,int k,
                                 map<vint,impldiff> & cterms,map<vint,gen> & pdf,map<vint,gen> & pdg,GIAC_CONTEXT) {
    int n=int(vars.size())-int(g.size());
    vector<vint> sigv;
    partition_m_in_n_terms(k,n,sigv);
    gen term(0);
    map<vint,gen> pdv;
    if (!g.empty())
        pdv=implicit_partial_derivatives(f,g,vars,k,vint(0),cterms,pdf,pdg,contextptr);
    for (vector<vint>::const_iterator it=sigv.begin();it!=sigv.end();++it) {
        gen pd;
        if (g.empty()) {
            vecteur args(1,f);
            for (int i=0;i<n;++i) {
                for (int j=0;j<it->at(i);++j) {
                    args.push_back(vars[i]);
                }
            }
            pd=_derive(_feuille(args,contextptr),contextptr);
        }
        else
            pd=pdv[*it];
        pd=subst(pd,vars,a,false,contextptr);
        for (int i=0;i<n;++i) {
            int ki=it->at(i);
            if (ki==0)
                continue;
            pd=pd*pow(vars[i]-a[i],ki)/factorial(ki);
        }
        term+=pd;
    }
    return term;
}

gen_map find_extrema(gen & f,vecteur & g,vecteur & vars,vecteur & initial,int order_size,GIAC_CONTEXT) {
    int nv=int(vars.size()),m=int(g.size()),n=nv-m;
    vecteur fvars(vars);
    fvars.resize(n);
    // determine critical points
    map<vint,impldiff> cterms;
    map<vint,gen> pdf,pdg,pdv;
    vecteur gr;
    if (m>0) {
        pdv=implicit_partial_derivatives(f,g,vars,1,vint(0),cterms,pdf,pdg,contextptr);
        gr=pdv2gradient(pdv,n);
    }
    else
        gr=*_grad(makesequence(f,vars),contextptr)._VECTptr;
    matrice cv,h;
    gen_map res;
    vecteur eqv(mergevecteur(gr,g));
    if (initial.empty())
        cv=solve2(eqv,vars,contextptr);
    else {
        vecteur fsol(*_fsolve(makesequence(eqv,vars,initial),contextptr)._VECTptr);
        if (!fsol.empty())
            cv.push_back(fsol);
    }
    // compute hessian
    if (m>0) {
        pdv=implicit_partial_derivatives(f,g,vars,2,vint(0),cterms,pdf,pdg,contextptr);
        h=pdv2hessian(pdv,n);
    }
    else
        h=*_hessian(makesequence(f,vars),contextptr)._VECTptr;
    // variables for Taylor expansion used in higher order test
    vecteur taylor_terms;
    vecteur a(nv);
    for (int i=0;i<nv;++i) {
        a[i]=make_idnt("a",i);
    }
    // try to classify critical points
    for (int i=cv.size()-1;i>=0;--i) {
        int cls=_CPCLASS_UNDECIDED;
        // second order test (using hessian)
        matrice H(*_evalf(subst(h,vars,cv[i],false,contextptr),contextptr)._VECTptr);
        bool ismax=true,ismin=true;
        int k=0;
        vecteur eigvals(*_eigenvals(H,contextptr)._VECTptr);
        for (;k<n;++k) {
            if (is_zero(eigvals[k]))
                break;
            if (is_positive(eigvals[k],contextptr))
                ismax=false;
            else
                ismin=false;
        }
        if (k==n)
            cls=ismin?_CPCLASS_MIN:(ismax?_CPCLASS_MAX:_CPCLASS_SADDLE);
        if (cls==_CPCLASS_UNDECIDED && order_size>=2) {
            // second order test was inconclusive, apply the extremum test which
            // requires computation of higher derivatives
            if (n==1 && order_size>2) {
                // univariate extremum test
                int k=2;  // degree of the derivative
                gen df;
                while (k<order_size) {
                    k++;
                    if (nv==1)
                        df=_derive(makesequence(f,vars[0],gen(k)),contextptr);
                    else {
                        vint sig(1,k);
                        df=implicit_partial_derivatives(f,g,vars,k,sig,cterms,pdf,pdg,contextptr)[sig];
                    }
                    if (is_undef(df) || is_zero(df))
                        break;
                    gen val=_evalf(subst(df,vars,cv[i],false,contextptr),contextptr);
                    if (is_undef(val) || is_inf(_abs(val,contextptr)))
                        break;
                    if (!is_zero(val)) {
                        // if k is odd there is no extremum at critical point, while for k even there
                        // is local minimum if 'val' is positive or local maximum if 'val' is negative
                        cls=(k%2)==0?(is_positive(val,contextptr)?_CPCLASS_MIN:_CPCLASS_MAX):_CPCLASS_SADDLE;
                        break;
                    }
                }
            }
            else if (n>1) {
                // higher derivative test for multivariate functions by Salvador Gigena
                // (Theorem 6.5 on page 27 in:  https://arxiv.org/abs/1303.3184)
                for (int k=2;k<=order_size;++k) {
                    if (int(taylor_terms.size())<k-1)
                        taylor_terms.push_back(compute_implicit_taylor_term(f,g,a,vars,k,cterms,pdf,pdg,contextptr));
                    if (is_zero(taylor_terms.back()))
                        break;
                    gen p=subst(taylor_terms[k-2],a,cv[i],false,contextptr);  // homogeneous poly
                    if (is_zero(p))
                        // kth homoheneous polynomial vanishes at cv[i]
                        continue;
                    // Compute minimal and maximal value of p on unit sphere S at cv[i]
                    gen pmin,pmax;
                    gen sphere(-1);
                    for (int j=0;j<n;++j) {
                        sphere+=pow(vars[j]-cv[i][j],2);
                    }
                    vecteur gp,hp(1,sphere);
                    vecteur loc(global_extrema(p,gp,hp,fvars,pmin,pmax,contextptr));
                    if (loc.empty())
                        // unable to find global extrema, abort classifying cv[i]
                        break;
                    if (is_zero(pmin) && is_zero(pmax))
                        // p vanishes in S
                        continue;
                    // p attains nonzero value somewhere in S, range(p)=[pmin,pmax]!=[0,0]
                    if (k%2 || (is_strictly_positive(-pmin,contextptr) && is_strictly_positive(pmax,contextptr))) {
                        // if the term is odd, cv[i] is a saddle point, or case c3
                        cls=_CPCLASS_SADDLE;
                        break;
                    }
                    // p is the first nonzero homogeneous polynomial
                    if (is_strictly_positive(pmin,contextptr)) {
                        // case c1: strict local minimum
                        cls=_CPCLASS_MIN;
                        break;
                    }
                    if (is_strictly_positive(-pmax,contextptr)) {
                        // case c2: strict local maximum
                        cls=_CPCLASS_MAX;
                        break;
                    }
                    if (is_zero(pmin)) {
                        // case c4: possible (non)strict local minimum
                        cls=_CPCLASS_POSSIBLE_MIN;
                        break;
                    }
                    if (is_zero(pmax)) {
                        // case c5: possible (non)strict local maximum
                        cls=_CPCLASS_POSSIBLE_MAX;
                        break;
                    }
                }
            }
        }
        res[*cv[i]._VECTptr]=gen(cls);
    }
    return res;
}

gen_map format_critical_points(gen_map & cv,vint & arr,vecteur & vars,GIAC_CONTEXT) {
    gen_map res;
    int n=int(vars.size());
    for (gen_map::const_iterator it=cv.begin();it!=cv.end();++it) {
        if (n==1)
            res[it->first._VECTptr->front()]=it->second;
        else if (arr.empty()) {
            res=cv;
            break;
        }
        else {
            vecteur v(n);
            for (int i=0;i<n;++i) {
                v[arr[i]]=_simplify(it->first._VECTptr->at(i),contextptr);
            }
            res[v]=it->second;
        }
    }
    return res;
}

/*
 * 'extrema' attempts to find all points of strict local minima/maxima of a
 * smooth (uni/multi)variate function subject to one or more equality
 * constraints. The implemented method uses Lagrange multipliers.
 *
 * Usage
 * ^^^^^
 *     extrema(expr,[constr],vars,[order_size])
 *
 * Parameters
 * ^^^^^^^^^^
 *   - expr                  : differentiable expression
 *   - constr (optional)     : (list of) equality constraint(s)
 *   - vars                  : (list of) problem variable(s)
 *   - order_size (optional) : specify 'order_size=<nonnegative integer>' to
 *                             bound the order of the derivatives being
 *                             inspected when classifying the critical points
 *
 * The number of constraints must be less than the number of variables. When
 * there are more than one constraint/variable, they must be specified in
 * form of list.
 *
 * Variables may be specified with symbol, e.g. 'var', or by using syntax
 * 'var=a..b', which restricts the variable 'var' to the open interval (a,b),
 * where a and b are real numbers or +/-infinity. If variable list includes a
 * specification of initial point, such as, for example, [x=1,y=0,z=2], then
 * numeric solver is activated to find critical point in the vicinity of the
 * given point. In this case, the single critical point, if found, is examined.
 *
 * The function attempts to find the critical points in exact form, if the
 * parameters of the problem are all exact. It works best for problems in which
 * the gradient of lagrangian function consists of rational expressions. The
 * result may be inexact, however, if exact solutions could not be obtained.
 *
 * For classifying critical points, the bordered hessian method is used first.
 * It is only a second order test, so it may be inconclusive in some cases. In
 * these cases function looks at higher-order derivatives, up to order
 * specified by 'order_size' option (the extremum test). Set 'order_size' to 1
 * to use only the bordered hessian test or 0 to output critical points without
 * attempting to classify them. Setting 'order_size' to 2 or higher will
 * activate checking for saddle points and inspecting higher derivatives (up to
 * 'order_size') to determine the nature of some or all unclassified critical
 * points. By default 'order_size' equals to 12.
 *
 * The return value is a sequence with two elements: list of strict local
 * minima and list of strict local maxima. If only critical points are
 * requested (by setting 'order_size' to 0), the output consists of a single
 * list, as no classification was attempted. For univariate problems the points
 * are real numbers, while for multivariate problems they are specified as
 * lists of coordinates, so "lists of points" are in fact matrices with rows
 * corresponding to points in multivariate cases, i.e. vectors in univariate
 * cases.
 *
 * The function prints out information about saddle/inflection points and also
 * about critical points for which no decision could be made, so that the user
 * can inspect candidates for local extrema by plotting the graph, for example.
 *
 * Examples
 * ^^^^^^^^
 * extrema(-2*cos(x)-cos(x)^2,x)
 *    >> [0],[pi]
 * extrema((x^3-1)^4/(2x^3+1)^4,x=0..inf)
 *    >> [1],[]
 * extrema(x/2-2*sin(x/2),x=-12..12)
 *    >> [2*pi/3,-10*pi/3],[10*pi/3,-2*pi/3]
 * extrema(x-ln(abs(x)),x)
 *    >> [1],[]
 * assume(a>=0);extrema(x^2+a*x,x)
 *    >> [-a/2],[]
 * extrema(x^7+3x^6+3x^5+x^4+2x^2-x,x)
 *    >> [0.225847362349],[-1.53862319761]
 * extrema((x^2+x+1)/(x^4+1),x)
 *    >> [],[0.697247087784]
 * extrema(x^2+exp(-x),x)
 *    >> [0.351733711249],[]
 * extrema(exp(-x)*ln(x),x)
 *    >> [],[1.76322283435]
 * extrema(tan(x)*(x^3-5x^2+1),x=-0.5)
 *    >> [-0.253519032024],[]
 * extrema(tan(x)*(x^3-5x^2+1),x=0.5)
 *    >> [],[0.272551772027]
 * extrema(exp(x^2-2x)*ln(x)*ln(1-x),x=0.5)
 *    >> [],[0.277769149124]
 * extrema(ln(2+x-sin(x)^2),x=0..2*pi)
 *    >> [],[] (needed to compute third derivative to drop critical points pi/4 and 5pi/4)
 * extrema(x^3-2x*y+3y^4,[x,y])
 *    >> [[12^(1/5)/3,(12^(1/5))^2/6]],[]
 * extrema((2x^2-y)*(y-x^2),[x,y])  //Peano surface
 *    >> [],[] (non-strict local maximum at origin)
 * extrema(5x^2+3y^2+x*z^2-z*y^2,[x,y,z])
 *    >> [],[] (non-strict local minimum at origin)
 * extrema(3*atan(x)-2*ln(x^2+y^2+1),[x,y])
 *    >> [],[[3/4,0]]
 * extrema(x*y,x+y=1,[x,y])
 *    >> [],[[1/2,1/2]]
 * extrema(sqrt(x*y),x+y=2,[x,y])
 *    >> [],[[1,1]]
 * extrema(x*y,x^3+y^3=16,[x,y])
 *    >> [],[[2,2]]
 * extrema(x^2+y^2,x*y=1,[x=0..inf,y=0..inf])
 *    >> [[1,1]],[]
 * extrema(ln(x*y^2),2x^2+3y^2=8,[x,y])
 *    >> [],[[2*sqrt(3)/3,-4/3],[-2*sqrt(3)/3,-4/3],[2*sqrt(3)/3,4/3],[-2*sqrt(3)/3,4/3]]
 * extrema(y^2+4y+2x-x^2,x+2y=2,[x,y])
 *    >> [],[[-2/3,4/3]]
 * assume(a>0);extrema(x/a^2+a*y^2,x+y=a,[x,y])
 *    >> [[(2*a^4-1)/(2*a^3),1/(2*a^3)]],[]
 * extrema(6x+3y+2z,4x^2+2y^2+z^2=70,[x,y,z])
 *    >> [[-3,-3,-4]],[[3,3,4]]
 * extrema(x*y*z,x+y+z=1,[x,y,z])
 *    >> [],[[1/3,1/3,1/3]]
 * extrema(x*y^2*z^2,x+y+z=5,[x,y,z])
 *    >> [],[[1,2,2]]
 * extrema(4y-2z,[2x-y-z=2,x^2+y^2=1],[x,y,z])
 *    >> [[2*sqrt(13)/13,-3*sqrt(13)/13,(7*sqrt(13)-26)/13]],
 *       [[-2*sqrt(13)/13,3*sqrt(13)/13,(-7*sqrt(13)-26)/13]]
 * extrema((x-3)^2+(y-1)^2+(z-1)^2,x^2+y^2+z^2=4,[x,y,z])
 *    >> [[6*sqrt(11)/11,2*sqrt(11)/11,2*sqrt(11)/11]],
 *       [[-6*sqrt(11)/11,-2*sqrt(11)/11,-2*sqrt(11)/11]]
 * extrema(x+3y-z,2x^2+y^2=z,[x,y,z])
 *    >> [],[[1/4,3/2,19/8]]
 * extrema(2x*y+2y*z+x*z,x*y*z=4,[x,y,z])
 *    >> [[2,1,2]],[]
 * extrema(x+y+z,[x^2+y^2=1,2x+z=1],[x,y,z])
 *    >> [[sqrt(2)/2,-sqrt(2)/2,-sqrt(2)+1]],[[-sqrt(2)/2,sqrt(2)/2,sqrt(2)+1]]
 * assume(a>0);extrema(x+y+z,[y^2-x^2=a,x+2z=1],[x,y,z])
 *    >> [[-sqrt(3)*sqrt(a)/3,2*sqrt(3)*sqrt(a)/3,(sqrt(3)*sqrt(a)+3)/6]],
 *       [[sqrt(3)*sqrt(a)/3,-2*sqrt(3)*sqrt(a)/3,(-sqrt(3)*sqrt(a)+3)/6]]
 * extrema((x-u)^2+(y-v)^2,[x^2/4+y^2/9=1,(u-3)^2+(v+5)^2=1],[u,v,x,y])
 *    >> [[2.35433932354,-4.23637555425,0.982084902545,-2.61340692712]],
 *       [[3.41406613851,-5.91024679428,-0.580422508346,2.87088778158]]
 * extrema(x2^6+x1^3+4x1+4x2,x1^5+x2^4+x1+x2=0,[x1,x2])
 *    >> [[-0.787457596325,0.758772338924],[-0.784754836317,-1.23363062357]],
 *       [[0.154340184382,-0.155005038065]]
 * extrema(x*y,-2x^3+15x^2*y+11y^3-24y=0,[x,y])
 *    >> [[sqrt(17)*sqrt(3*sqrt(33)+29)/17,sqrt(-15*sqrt(33)+127)*sqrt(187)/187],
 *        [-sqrt(17)*sqrt(3*sqrt(33)+29)/17,-sqrt(-15*sqrt(33)+127)*sqrt(187)/187],
 *        [sqrt(-3*sqrt(33)+29)*sqrt(17)/17,-sqrt(15*sqrt(33)+127)*sqrt(187)/187],
 *        [-sqrt(-3*sqrt(33)+29)*sqrt(17)/17,sqrt(15*sqrt(33)+127)*sqrt(187)/187]],
 *       [[1,1],[-1,-1],[0,0]]
 * extrema(x2^4-x1^4-x2^8+x1^10,[x1,x2],order_size=1)
 *    >> [[0,0],[0,-(1/2)^(1/4)],[0,(1/2)^(1/4)],[-(2/5)^(1/6),0],[-(2/5)^(1/6),-(1/2)^(1/4)],
 *        [-(2/5)^(1/6),(1/2)^(1/4)],[(2/5)^(1/6),0],[(2/5)^(1/6),-(1/2)^(1/4)],[(2/5)^(1/6),(1/2)^(1/4)]]
 * extrema(x2^4-x1^4-x2^8+x1^10,[x1,x2])
 *    >> [[(2/5)^(1/6),0],[-(2/5)^(1/6),0]],[[0,(1/2)^(1/4)],[0,-(1/2)^(1/4)]]
 * extrema(x2^6+x1^3+4x1+4x2,x1^5+x2^4+x1+x2=0,[x1,x2])
 *    >> [[-0.787457596325,0.758772338924],[-0.784754836317,-1.23363062357]],
 *       [[0.154340184382,-0.155005038065]]
 * extrema(x2^6+x1^3+2x1^2-x2^2+4x1+4x2,x1^5+x2^4+x1+x2=0,[x1,x2])
 *    >> [[-0.662879934158,-1.18571027742],[0,0]],[[0.301887394815,-0.314132376868]]
 * extrema(3x^2-2x*y+y^2-8y,[x,y])
 *    >> [[2,6]],[]
 * extrema(x^3+3x*y^2-15x-12y,[x,y])
 *    >> [[2,1]],[[-2,-1]]
 * extrema(4x*y-x^4-y^4,[x,y])
 *    >> [],[[1,1],[-1,-1]]
 * extrema(x*sin(y),[x,y])
 *    >> [],[]
 * extrema(x^4+y^4,[x,y])
 *    >> [[0,0]],[]
 * extrema(x^3*y-x*y^3,[x,y])  //dog saddle at origin
 *    >> [],[]
 * extrema(x^2+y^2+z^2,x^4+y^4+z^4=1,[x,y,z])
 *    >> [[0,0,1],[0,0,-1]],[]
 * extrema(3x+3y+8z,[x^2+z^2=1,y^2+z^2=1],[x,y,z])
 *    >> [[-3/5,-3/5,-4/5]],[[3/5,3/5,4/5]]
 * extrema(2x^2+y^2,x^4-x^2+y^2=5,[x,y])
 *    >> [[0,-sqrt(5)],[0,sqrt(5)]],
 *       [[-1/2*sqrt(6),-1/2*sqrt(17)],[-1/2*sqrt(6),1/2*sqrt(17)],
 *        [1/2*sqrt(6),-1/2*sqrt(17)],[1/2*sqrt(6),1/2*sqrt(17)]]
 * extrema((3x^4-4x^3-12x^2+18)/(12*(1+4y^2)),[x,y])
 *    >> [[2,0]],[[0,0]]
 * extrema(x-y+z,[x^2+y^2+z^2=1,x+y+2z=1],[x,y,z])
 *    >> [[(-2*sqrt(70)+7)/42,(4*sqrt(70)+7)/42,(-sqrt(70)+14)/42]],
 *       [[(2*sqrt(70)+7)/42,(-4*sqrt(70)+7)/42,(sqrt(70)+14)/42]]
 * extrema(ln(x)+2*ln(y)+3*ln(z)+4*ln(u)+5*ln(v),x+y+z+u+v=1,[x,y,z,u,v])
 *    >> [],[[1/15,2/15,1/5,4/15,1/3]]
 * extrema(x*y*z,-2x^3+15x^2*y+11y^3-24y=0,[x,y,z])
 *    >> [],[]
 * extrema(x+y-exp(x)-exp(y)-exp(x+y),[x,y])
 *    >> [],[[ln(-1/2*(-sqrt(5)+1)),ln(-1/2*(-sqrt(5)+1))]]
 * extrema(x^2*sin(y)-4*x,[x,y])    // has two saddle points
 *    >> [],[]
 * extrema((1+y*sinh(x))/(1+y^2+tanh(x)^2),[x,y])
 *    >> [],[[0,0]]
 * extrema((1+y*sinh(x))/(1+y^2+tanh(x)^2),y=x^2,[x,y])
 *    >> [[1.42217627369,2.02258535346]],[[8.69443642205e-16,7.55932246971e-31]]
 */
gen _extrema(const gen & g,GIAC_CONTEXT) {
    if (g.type==_STRNG && g.subtype==-1) return g;
    if (g.type!=_VECT || g.subtype!=_SEQ__VECT)
        return gentypeerr(contextptr);
    vecteur & gv = *g._VECTptr,constr;
    int order_size=5; // will not compute derivatives of order higher than 'order_size'
    int ngv=gv.size();
    if (gv.back().is_symb_of_sommet(at_equal)) {
        vecteur & v = *gv.back()._SYMBptr->feuille._VECTptr;
        if (v[0]==at_order_size && is_integer(v[1])) {
            order_size=v[1].val;
            --ngv;
        }
    }
    if (ngv<2 || ngv>3)
        return gensizeerr(contextptr);
    // get the variables
    int nv;
    vecteur vars,oldvars,initial;
    // parse variables and their ranges, if given
    if ((nv=(oldvars=parse_varlist(gv,ngv,vars,initial,contextptr)).size())==0)
        return gentypeerr(contextptr);
    if (!initial.empty() && int(initial.size())<nv)
        return gensizeerr(contextptr);
    if (ngv==3) {
        // get the constraints
        if (gv[1].type==_VECT)
            constr=*gv[1]._VECTptr;
        else
            constr=vecteur(1,gv[1]);
    }
    for (int i=0;i<int(constr.size());++i) {
        if (constr[i].is_symb_of_sommet(at_equal))
            constr[i]=equal2diff(constr[i]);
    }
    vint arr;
    if (!constr.empty()) {
        matrice J(jacobian(constr,oldvars,contextptr));
        if (_rank(J,contextptr).val<int(constr.size())) {
            cout << "Error: too many constraints" << endl;
            return gendimerr(contextptr);
        }
        arr=rearrange_vars(J,contextptr);
    }
    vecteur tmp_vars,tmp_oldvars;
    if (!arr.empty()) {
        for (vint::const_iterator it=arr.begin();it!=arr.end();++it) {
            tmp_vars.push_back(vars[*it]);
            tmp_oldvars.push_back(oldvars[*it]);
        }
        vars=tmp_vars;
    }
    constr=subst(constr,arr.empty()?oldvars:tmp_oldvars,vars,false,contextptr);
    gen f(subst(gv[0],arr.empty()?oldvars:tmp_oldvars,vars,false,contextptr));
    gen_map res(find_extrema(f,constr,vars,initial,order_size,contextptr));
    res=format_critical_points(res,arr,oldvars,contextptr);
    if (order_size<2) {
        // return list of critical points
        vecteur cv;
        for (gen_map::const_iterator it=res.begin();it!=res.end();++it) {
            cv.push_back(it->first);
        }
        return cv;
    }
    // return sequence of minima and maxima in separate lists and report non-extrema
    vecteur minv,maxv;
    for (gen_map::const_iterator it=res.begin();it!=res.end();++it) {
        gen dispt(nv==1?symb_equal(oldvars[0],it->first):_zip(makesequence(at_equal,oldvars,it->first),contextptr));
        switch(it->second.val) {
        case _CPCLASS_MIN:
            minv.push_back(it->first);
            break;
        case _CPCLASS_MAX:
            maxv.push_back(it->first);
            break;
        case _CPCLASS_SADDLE:
            cout << dispt << (nv==1?": inflection point":": saddle point") << endl;
            break;
        case _CPCLASS_POSSIBLE_MIN:
            cout << dispt << ": possible local minimum" << endl;
            break;
        case _CPCLASS_POSSIBLE_MAX:
            cout << dispt << ": possible local maximum" << endl;
            break;
        case _CPCLASS_UNDECIDED:
            cout << dispt << ": unclassified critical point" << endl;
            break;
        }
    }
    return makesequence(minv,maxv);
}
static const char _extrema_s []="extrema";
static define_unary_function_eval (__extrema,&_extrema,_extrema_s);
define_unary_function_ptr5(at_extrema,alias_at_extrema,&__extrema,0,true)

/*
 * Compute the value of expression f(var) (or |f(var)| if 'absolute' is true)
 * for var=a.
 */
gen compf(const gen & f,identificateur & x,gen & a,bool absolute,GIAC_CONTEXT) {
    gen val(subst(f,x,a,false,contextptr));
    return _evalf(absolute?_abs(val,contextptr):val,contextptr);
}

/*
 * find zero of expression f(x) for x in [a,b] using Brent solver
 */
gen find_zero(const gen & f,identificateur & x,gen & a,gen & b,GIAC_CONTEXT) {
    gen I(symb_interval(a,b));
    gen var(symb_equal(x,I));
    vecteur sol(*_fsolve(makesequence(f,var,_BRENT_SOLVER),contextptr)._VECTptr);
    return sol.empty()?(a+b)/2:sol[0];
}

/*
 * Find point of maximum/minimum of unimodal expression f(x) in [a,b] using the
 * golden-section search.
 */
gen find_peak(const gen & f,identificateur & x,gen & a_orig,gen & b_orig,GIAC_CONTEXT) {
    gen a(a_orig),b(b_orig);
    gen c(b-(b-a)/GOLDEN_RATIO),d(a+(b-a)/GOLDEN_RATIO);
    while (is_strictly_greater(_abs(c-d,contextptr),epsilon(contextptr),contextptr)) {
        gen fc(compf(f,x,c,true,contextptr)),fd(compf(f,x,d,true,contextptr));
        if (is_strictly_greater(fc,fd,contextptr))
            b=d;
        else
            a=c;
        c=b-(b-a)/GOLDEN_RATIO;
        d=a+(b-a)/GOLDEN_RATIO;
    }
    return (a+b)/2;
}

/*
 * Compute n Chebyshev nodes in [a,b].
 */
vecteur chebyshev_nodes(gen & a,gen & b,int n,GIAC_CONTEXT) {
    vecteur nodes(1,a);
    for (int i=1;i<=n;++i) {
        nodes.push_back(_evalf((a+b)/2+(b-a)*symbolic(at_cos,((2*i-1)*cst_pi/(2*n)))/2,contextptr));
    }
    nodes.push_back(b);
    return *_sort(nodes,contextptr)._VECTptr;
}

/*
 * Implementation of Remez method for minimax polynomial approximation of a
 * continuous bounded function, which is not necessary differentiable in all
 * points of (a,b).
 *
 * Source: http://homepages.rpi.edu/~tasisa/remez.pdf
 *
 * Usage
 * ^^^^^
 *      minimax(expr,var=a..b,n,[opts])
 *
 * Parameters
 * ^^^^^^^^^^
 *      - expr            : expression to be approximated on [a,b]
 *      - var             : variable
 *      - a,b             : bounds of the function domain
 *      - n               : degree of the minimax approximation polynomial
 *      - opts (optional) : sequence of options
 *
 * This function uses 'compf', 'find_zero' and 'find_peak'. It does not use
 * derivatives to determine points of local extrema of error function, but
 * instead implements the golden search algorithm to find these points in the
 * exchange phase of Remez method.
 *
 * The returned polynomial may have degree lower than n, because the latter is
 * decremented during execution of the algorithm if there is no unique solution
 * for coefficients of a nth degree polynomial. After each decrement, the
 * algorithm is restarted. If the degree of resulting polynomial is m<n, it
 * means that polynomial of degree between m and n cannot be obtained by using
 * this implementation.
 *
 * In 'opts' one may specify 'limit=<posint>' which limits the number of
 * iterations. By default, it is unlimited.
 *
 * Be aware that, in some cases, the result with high n may be unsatisfying,
 * producing larger error than the polynomials for smaller n. This happens
 * because of the rounding errors. Nevertheless, a good approximation of an
 * "almost" smooth function can usually be obtained with n less than 30. Highly
 * oscillating functions containing sharp cusps and spikes will probably be
 * approximated poorly.
 *
 * Examples
 * ^^^^^^^^
 * minimax(x*exp(-x),x=0..10,24)
 * minimax(x*sin(x),x=0..10,25)
 * minimax(ln(2+x-sin(x)^2),x=0..2*pi,20)
 * minimax(cos(x^2-x+1),x=-2..2,40)
 * minimax(atan(x),x=-5..5,25)
 * minimax(tanh(sin(9x)),x=-1/2..1/2,40)
 * minimax(abs(x),x=-1..1,20)
 * minimax(abs(x)*sqrt(abs(x)),x=-2..2,15)
 * minimax(min(1/cosh(3*sin(10x)),sin(9x)),x=-0.3..0.4,25)
 * minimax(when(x==0,0,exp(-1/x^2)),x=-1..1,30)
 */
gen _minimax(const gen & g,GIAC_CONTEXT) {
    if (g.type==_STRNG && g.subtype==-1) return g;
    if (g.type!=_VECT || g.subtype!=_SEQ__VECT)
        return gentypeerr(contextptr);
    vecteur & gv = *g._VECTptr;
    if (gv.size()<3)
        return gensizeerr(contextptr);
    if (!gv[1].is_symb_of_sommet(at_equal) || !is_integer(gv[2]))
        return gentypeerr(contextptr);
    // detect parameters
    vecteur s(*gv[1]._SYMBptr->feuille._VECTptr);
    if (s[0].type!=_IDNT || !s[1].is_symb_of_sommet(at_interval))
        return gentypeerr((contextptr));
    identificateur x(*s[0]._IDNTptr);
    s=*s[1]._SYMBptr->feuille._VECTptr;
    gen a(_evalf(s[0],contextptr)),b(_evalf(s[1],contextptr));
    if (!is_strictly_greater(b,a,contextptr))
        return gentypeerr(contextptr);
    gen & f=gv[0];
    int n=gv[2].val;
    gen threshold(1.02);  // threshold for stopping criterion
    // detect options
    int limit=0;
    //bool poly=true;
    for (const_iterateur it=gv.begin()+3;it!=gv.end();++it) {
        if (it->is_symb_of_sommet(at_equal)) {
            vecteur & p=*it->_SYMBptr->feuille._VECTptr;
            if (p[0]==at_limit) {
                if (!is_integer(p[1]) || !is_strictly_positive(p[1],contextptr))
                    return gentypeerr(contextptr);
                limit=p[1].val;
            }
        }
        else if (is_integer(*it)) {
            switch (it->val) {
//          case _FRAC:
//              poly=false;
//              break;
            }
        }
    }
    // create Chebyshev nodes to start with
    vecteur nodes(chebyshev_nodes(a,b,n,contextptr));
    gen p,best_p,best_emax,emax,emin;
    int iteration_count=0;
    while (true) { // iterate the algorithm
        iteration_count++;
        if (n<1 || (limit>0 && iteration_count>limit))
            break;
        // compute polynomial p
        matrice m;
        vecteur fv;
        for (int i=0;i<n+2;++i) {
            fv.push_back(_evalf(subst(f,x,nodes[i],false,contextptr),contextptr));
            vecteur r;
            for (int j=0;j<n+1;++j) {
                r.push_back(j==0?gen(1):pow(nodes[i],j));
            }
            r.push_back(pow(gen(-1),i));
            m.push_back(r);
        }
        vecteur sol(*_linsolve(makesequence(m,fv),contextptr)._VECTptr);
        if (!_lname(sol,contextptr)._VECTptr->empty()) {
            // Solution is not unique, it contains a symbol.
            // Decrease n and start over.
            nodes=chebyshev_nodes(a,b,--n,contextptr);
            continue;
        }
        p=gen(0);
        for (int i=0;i<n+1;++i) {
            p+=sol[i]*pow(x,i);
        }
        // compute the error function and its zeros
        gen e(f-p);
        vecteur zv(1,a);
        for (int i=0;i<n+1;++i) {
            zv.push_back(find_zero(e,x,nodes[i],nodes[i+1],contextptr));
        }
        zv.push_back(b);
        // remez exchange:
        // determine points of local extrema of error function e
        vecteur ev(n+2,0);
        for (int i=0;i<n+2;++i) {
            if (i>0 && i<n+1) {
                nodes[i]=find_peak(e,x,zv[i],zv[i+1],contextptr);
                ev[i]=compf(e,x,nodes[i],true,contextptr);
                continue;
            }
            gen e1(compf(e,x,zv[i],true,contextptr)),e2(compf(e,x,zv[i+1],true,contextptr));
            if (is_greater(e1,e2,contextptr)) {
                nodes[i]=zv[i];
                ev[i]=e1;
            }
            else {
                nodes[i]=zv[i+1];
                ev[i]=e2;
            }
        }
        // compute minimal and maximal absolute error
        emin=_min(ev,contextptr);
        emax=_max(ev,contextptr);
        if (is_exactly_zero(best_emax) || is_strictly_greater(best_emax,emax,contextptr)) {
            best_p=p;
            best_emax=emax;
        }
        // emin >= E is required to continue, also check
        // if the threshold is reached, i.e. the difference
        // between emax and emin is at least fifty times
        // smaller than emax
        if (is_strictly_greater(sol.back(),emin,contextptr) ||
                is_greater(threshold*emin,emax,contextptr)) {
            break;
        }
    }
    cout << "max. absolute error: " << best_emax << endl;
    return best_p;
}
static const char _minimax_s []="minimax";
static define_unary_function_eval (__minimax,&_minimax,_minimax_s);
define_unary_function_ptr5(at_minimax,alias_at_minimax,&__minimax,0,true)

/*
 * North-West-Corner method giving the initial feasible solution to the
 * transportatiom problem with given supply and demand vectors. It handles
 * degeneracy cases (assignment problems, for example, always have degenerate
 * solutions).
 */
matrice north_west_corner(vecteur & supply,vecteur & demand,GIAC_CONTEXT) {
    int m=supply.size(),n=demand.size();
    gen eps(exact(epsilon(contextptr)/2,contextptr));
    matrice X;
    for (int k=0;k<m;++k) {
        X.push_back(vecteur(n,0));
    }
    int i=0,j=0;
    while (i<m && j<n) {
        gen u,v;
        for (int k=0;k<i;++k) {
            v+=_epsilon2zero(X[k][j],contextptr);
        }
        for (int k=0;k<j;++k) {
            u+=_epsilon2zero(X[i][k],contextptr);
        }
        gen a(_min(makesequence(supply[i]-u,demand[j]-v),contextptr));
        X[i]._VECTptr->at(j)=a;
        int k=i+j;
        if (u+a==supply[i])
            ++i;
        if (v+a==demand[j])
            ++j;
        if (i<m && j<n && i+j-k==2) {
            // avoid degeneracy
            X[i-1]._VECTptr->at(j)=eps;
        }
    }
    return X;
}

/*
 * Stepping stone path method for determining a closed path "jumping" from one
 * positive element of X to another in the same row or column.
 */
vector<pint> stepping_stone_path(vector<pint> & path_orig,matrice & X,GIAC_CONTEXT) {
    vector<pint> path(path_orig);
    int I=path.back().first,J=path.back().second;
    int m=X.size(),n=X.front()._VECTptr->size();
    if (path.size()>1 && path.front().second==J)
        return path;
    bool hrz=path.size()%2==1;
    for (int i=0;i<(hrz?n:m);++i) {
        int cnt=0;
        for (vector<pint>::const_iterator it=path.begin();it!=path.end();++it) {
            if ((hrz && it->second==i) || (!hrz && it->first==i))
                ++cnt;
        }
        if (cnt<2 && !is_exactly_zero(X[hrz?I:i][hrz?i:J])) {
            path.push_back(make_pair(hrz?I:i,hrz?i:J));
            vector<pint> fullpath(stepping_stone_path(path,X,contextptr));
            if (!fullpath.empty())
                return fullpath;
            path.pop_back();
        }
    }
    return vector<pint>(0);
}

/*
 * Implementation of MODI (modified ditribution) method. It handles degenerate
 * solutions if they appear during the process.
 */
void modi(matrice & P_orig,matrice & X,gen & M,GIAC_CONTEXT) {
    matrice P(P_orig);
    int m=X.size(),n=X.front()._VECTptr->size();
    vecteur u(m),v(n);
    gen eps(exact(epsilon(contextptr)/2,contextptr));
    if (M.type==_IDNT) {
        gen largest(0);
        for (int i=0;i<m;++i) {
            for (int j=0;j<n;++j) {
                if (is_greater(X[i][j],largest,contextptr))
                    largest=X[i][j];
            }
        }
        P=subst(P,M,100*largest,false,contextptr);
    }
    for (int i=0;i<m;++i) {
        u[i]=i==0?gen(0):make_idnt("u",i);
    }
    for (int j=0;j<n;++j) {
        v[j]=make_idnt("v",j);
    }
    vecteur vars(mergevecteur(vecteur(u.begin()+1,u.end()),v));
    while (true) {
        vecteur eqv;
        for (int i=0;i<m;++i) {
            for (int j=0;j<n;++j) {
                if (!is_exactly_zero(X[i][j]))
                    eqv.push_back(u[i]+v[j]-P[i][j]);
            }
        }
        vecteur sol(*_linsolve(makesequence(eqv,vars),contextptr)._VECTptr);
        vecteur U(1,0),V(sol.begin()+m-1,sol.end());
        U=mergevecteur(U,vecteur(sol.begin(),sol.begin()+m-1));
        gen cmin(0);
        bool optimal=true;
        int I,J;
        for (int i=0;i<m;++i) {
            for (int j=0;j<n;++j) {
                if (is_exactly_zero(X[i][j])) {
                    gen c(P[i][j]-U[i]-V[j]);
                    if (is_strictly_greater(cmin,c,contextptr)) {
                        cmin=c;
                        optimal=false;
                        I=i;
                        J=j;
                    }
                }
            }
        }
        if (optimal)
            break;
        vector<pint> path;
        path.push_back(make_pair(I,J));
        path=stepping_stone_path(path,X,contextptr);
        gen d(X[path.at(1).first][path.at(1).second]);
        for (vector<pint>::const_iterator it=path.begin()+3;it<path.end();it+=2) {
            d=_min(makesequence(d,X[it->first][it->second]),contextptr);
        }
        for (int i=0;i<int(path.size());++i) {
            gen & Xij=X[path.at(i).first]._VECTptr->at(path.at(i).second);
            gen x(Xij+(i%2?-d:d));
            bool has_zero=false;
            for (vector<pint>::const_iterator it=path.begin();it!=path.end();++it) {
                if (is_exactly_zero(X[it->first][it->second])) {
                    has_zero=true;
                    break;
                }
            }
            if ((!is_exactly_zero(x) && is_strictly_greater(gen(1)/gen(2),x,contextptr)) ||
                    (is_exactly_zero(x) && has_zero))
                x=eps;
            Xij=x;
        }
    }
    X=*exact(_epsilon2zero(_evalf(X,contextptr),contextptr),contextptr)._VECTptr;
}

/*
 * Function 'tpsolve' solves a transportation problem using MODI method.
 *
 * Usage
 * ^^^^^
 *      tpsolve(supply,demand,cost_matrix)
 *
 * Parameters
 * ^^^^^^^^^^
 *      - supply      : source capacity (vector of m positive integers)
 *      - demand      : destination demand (vector of n positive integers)
 *      - cost_matrix : real matrix C=[c_ij] of type mXn where c_ij is cost of
 *                      transporting an unit from ith source to jth destination
 *                      (a nonnegative number)
 *
 * Supply and demand vectors should contain only positive integers. Cost matrix
 * must be consisted of nonnegative real numbers, which do not have to be
 * integers. There is a possibility of adding a certain symbol to cost matrix,
 * usually M, to indicate the "infinite cost", effectively forbidding the
 * transportation on a certain route. The notation of the symbol may be chosen
 * arbitrarily, but must be used consistently within a single problem.
 *
 * The return value is a sequence of total (minimal) cost and matrix X=[x_ij]
 * of type mXn where x_ij is equal to number of units which have to be shipped
 * from ith source to jth destination, for all i=1,2,..,m and j=1,2,..,n.
 *
 * This function uses 'north_west_corner' to determine initial feasible
 * solution and then applies MODI method to optimize it (function 'modi', which
 * uses 'stepping_stone_path'). Also, it is capable of handling degeneracy of
 * the initial solution and during iterations of MODI method.
 *
 * If the given problem is not balanced, i.e. if supply exceeds demand or vice
 * versa, dummy supply/demand points will be automatically added to the
 * problem, augmenting the cost matrix with zeros. Resulting matrix will not
 * contain dummy point.
 *
 * Examples
 * ^^^^^^^^
 * Balanced transportation problem:
 *  tpsolve([12,17,11],[10,10,10,10],[[500,750,300,450],[650,800,400,600],[400,700,500,550]])
 *      >> 2020,[[0,0,2,10],[0,9,8,0],[10,1,0,0]]
 * Non-balanced transportation problem:
 *  tpsolve([7,10,8,8,9,6],[9,6,12,8,10],[[36,40,32,43,29],[28,27,29,40,38],[34,35,41,29,31],[41,42,35,27,36],[25,28,40,34,38],[31,30,43,38,40]])
 *      >> [[0,0,2,0,5],[0,0,10,0,0],[0,0,0,0,5],[0,0,0,8,0],[9,0,0,0,0],[0,6,0,0,0]]
 * Transportation problem with forbidden routes:
 *  tpsolve([95,70,165,165],[195,150,30,45,75],[[15,M,45,M,0],[12,40,M,M,0],[0,15,25,25,0],[M,0,M,12,0]])
 *      >> [[20,0,0,0,75],[70,0,0,0,0],[105,0,30,30,0],[0,150,0,15,0]]
 * Assignment problem:
 *  tpsolve([1,1,1,1],[1,1,1,1],[[10,12,9,11],[5,10,7,8],[12,14,13,11],[8,15,11,9]])
 *      >> [[0,0,1,0],[1,0,0,0],[0,1,0,0],[0,0,0,1]]
 */
gen _tpsolve(const gen & g,GIAC_CONTEXT) {
    if (g.type==_STRNG && g.subtype==-1) return g;
    if (g.type!=_VECT || g.subtype!=_SEQ__VECT)
        return gentypeerr(contextptr);
    vecteur & gv = *g._VECTptr;
    if (gv.size()<3)
        return gensizeerr(contextptr);
    if (gv[0].type!=_VECT || gv[1].type!=_VECT ||
            gv[2].type!=_VECT || !ckmatrix(*gv[2]._VECTptr))
        return gentypeerr(contextptr);
    vecteur supply(*gv[0]._VECTptr),demand(*gv[1]._VECTptr);
    matrice P(*gv[2]._VECTptr);
    vecteur sy(*_lname(P,contextptr)._VECTptr);
    int m=supply.size(),n=demand.size();
    if (sy.size()>1 || m!=int(P.size()) || n!=int(P.front()._VECTptr->size()))
        return gensizeerr(contextptr);
    gen M(sy.size()==1 && sy[0].type==_IDNT?sy[0]:0);
    gen ts(_sum(supply,contextptr)),td(_sum(demand,contextptr));
    if (ts!=td) {
        cout << "Warning: transportation problem is not balanced" << endl;
        if (is_greater(ts,td,contextptr)) {
            demand.push_back(ts-td);
            P=mtran(P);
            P.push_back(vecteur(m,0));
            P=mtran(P);
        }
        else {
            supply.push_back(td-ts);
            P.push_back(vecteur(n,0));
        }
    }
    matrice X(north_west_corner(supply,demand,contextptr));
    modi(P,X,M,contextptr);
    if (is_strictly_greater(ts,td,contextptr)) {
        X=mtran(X);
        X.pop_back();
        X=mtran(X);
    }
    else if (is_strictly_greater(td,ts,contextptr))
        X.pop_back();
    gen cost(0);
    for (int i=0;i<m;++i) {
        for (int j=0;j<n;++j) {
            cost+=P[i][j]*X[i][j];
        }
    }
    return makesequence(cost,X);
}
static const char _tpsolve_s []="tpsolve";
static define_unary_function_eval (__tpsolve,&_tpsolve,_tpsolve_s);
define_unary_function_ptr5(at_tpsolve,alias_at_tpsolve,&__tpsolve,0,true)

gen compute_invdiff(int n,int k,vecteur & xv,vecteur & yv,map< pint,gen > & invdiff,GIAC_CONTEXT) {
    pint I=make_pair(n,k);
    assert(n<=k);
    gen res(invdiff[I]);
    if (!is_zero(res))
        return res;
    if (n==0)
        return invdiff[I]=yv[k];
    if (n==1)
        return invdiff[I]=(xv[k]-xv[0])/(yv[k]-yv[0]);
    gen d1(compute_invdiff(n-1,n-1,xv,yv,invdiff,contextptr));
    gen d2(compute_invdiff(n-1,k,xv,yv,invdiff,contextptr));
    return invdiff[I]=(xv[k]-xv[n-1])/(d2-d1);
}

gen thiele(int k,vecteur & xv,vecteur & yv,identificateur & var,map< pint,gen > & invdiff,GIAC_CONTEXT) {
    if (k==int(xv.size()))
        return gen(0);
    gen phi(compute_invdiff(k,k,xv,yv,invdiff,contextptr));
    return (var-xv[k-1])/(phi+thiele(k+1,xv,yv,var,invdiff,contextptr));
}

/*
 * 'thiele' computes rational interpolation for the given list of points using
 * Thiele's method with continued fractions.
 *
 * Source: http://www.astro.ufl.edu/~kallrath/files/pade.pdf (see page 19)
 *
 * Usage
 * ^^^^^
 *      thiele(data,v)
 * or   thiele(data_x,data_y,v)
 *
 * Parameters
 * ^^^^^^^^^^
 *      - data      : list of points [[x1,y1],[x2,y2],...,[xn,yn]]
 *      - v         : identifier (may be any symbolic expression)
 *      - data_x    : list of x coordinates [x1,x2,...,xn]
 *      - data_y    : list of y coordinates [y1,y2,...,yn]
 *
 * The return value is an expression R(v), where R is rational interpolant of
 * the given set of points.
 *
 * Note that the interpolant may have singularities in
 * [min(data_x),max(data_x)].
 *
 * Example
 * ^^^^^^^
 * Function f(x)=(1-x^4)*exp(1-x^3) is sampled on interval [-1,2] in 13
 * equidistant points:
 *
 * data_x:=[-1,-0.75,-0.5,-0.25,0,0.25,0.5,0.75,1,1.25,1.5,1.75,2],
 * data_y:=[0.0,2.83341735599,2.88770329586,2.75030303645,2.71828182846,
 *          2.66568510781,2.24894558809,1.21863761951,0.0,-0.555711613283,
 *         -0.377871362418,-0.107135851128,-0.0136782294833]
 *
 * To obtain rational function passing through these points, input:
 *      thiele(data_x,data_y,x)
 * Output:
 *      (-1.55286115659*x^6+5.87298387514*x^5-5.4439152812*x^4+1.68655817708*x^3
 *       -2.40784868317*x^2-7.55954205222*x+9.40462512097)/(x^6-1.24295718965*x^5
 *       -1.33526268624*x^4+4.03629272425*x^3-0.885419321*x^2-2.77913222418*x+3.45976823393)
 */
gen _thiele(const gen & g,GIAC_CONTEXT) {
    if (g.type==_STRNG && g.subtype==-1) return g;
    if (g.type!=_VECT || g.subtype!=_SEQ__VECT)
        return gentypeerr(contextptr);
    vecteur & gv = *g._VECTptr;
    if (gv.size()<2)
        return gensizeerr(contextptr);
    vecteur xv,yv;
    gen x;
    if (gv[0].type!=_VECT)
        return gentypeerr(contextptr);
    if (ckmatrix(gv[0])) {
        matrice m(mtran(*gv[0]._VECTptr));
        if (m.size()!=2)
            return gensizeerr(contextptr);
        xv=*m[0]._VECTptr;
        yv=*m[1]._VECTptr;
        x=gv[1];
    }
    else {
        if (gv[1].type!=_VECT)
            return gentypeerr(contextptr);
        if (gv[0]._VECTptr->size()!=gv[1]._VECTptr->size())
            return gensizeerr(contextptr);
        xv=*gv[0]._VECTptr;
        yv=*gv[1]._VECTptr;
        x=gv[2];
    }
    gen var(x.type==_IDNT?x:identificateur(" x"));
    map< pint,gen > invdiff;
    gen rat(yv[0]+thiele(1,xv,yv,*var._IDNTptr,invdiff,contextptr));
    if (x.type==_IDNT) {
        // detect singularities
        gen den(_denom(rat,contextptr));
        matrice sing;
        if (*_lname(den,contextptr)._VECTptr==vecteur(1,x)) {
            for (int i=0;i<int(xv.size())-1;++i) {
                gen y1(_evalf(subst(den,x,xv[i],false,contextptr),contextptr));
                gen y2(_evalf(subst(den,x,xv[i+1],false,contextptr),contextptr));
                if (is_positive(-y1*y2,contextptr))
                    sing.push_back(makevecteur(xv[i],xv[i+1]));
            }
        }
        if (!sing.empty()) {
            cout << "Warning, the interpolant has singularities in ";
            for (int i=0;i<int(sing.size());++i) {
                cout << "(" << sing[i][0] << "," << sing[i][1] << ")";
                if (i<int(sing.size())-1)
                    cout << (i<int(sing.size())-2?", ":" and ");
            }
            cout << endl;
        }
    }
    else
        rat=_simplify(subst(rat,var,x,false,contextptr),contextptr);
    return ratnormal(rat,contextptr);
}
static const char _thiele_s []="thiele";
static define_unary_function_eval (__thiele,&_thiele,_thiele_s);
define_unary_function_ptr5(at_thiele,alias_at_thiele,&__thiele,0,true)

#ifndef NO_NAMESPACE_GIAC
}
#endif // ndef NO_NAMESPACE_GIAC
