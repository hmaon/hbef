# This file was created automatically by SWIG.
import hbefc
class coord:
    def __init__(self,*args):
        self.this = apply(hbefc.new_coord,args)
        self.thisown = 1

    def __del__(self,hbefc=hbefc):
        if getattr(self,'thisown',0):
            hbefc.delete_coord(self)
    __setmethods__ = {}
    for _s in []: __setmethods__.update(_s.__setmethods__)
    __setmethods__.update({
        "x" : hbefc.coord_x_set,
        "y" : hbefc.coord_y_set,
    })
    def __setattr__(self,name,value):
        if (name == "this") or (name == "thisown"): self.__dict__[name] = value; return
        method = coord.__setmethods__.get(name,None)
        if method: return method(self,value)
        self.__dict__[name] = value
    __getmethods__ = {}
    for _s in []: __getmethods__.update(_s.__getmethods__)
    __getmethods__.update({
        "x" : hbefc.coord_x_get,
        "y" : hbefc.coord_y_get,
    })
    def __getattr__(self,name):
        method = coord.__getmethods__.get(name,None)
        if method: return method(self)
        raise AttributeError,name
    def __repr__(self):
        return "<C coord instance at %s>" % (self.this,)
class coordPtr(coord):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
        self.__class__ = coord



class stackt:
    def __init__(self,*args):
        self.this = apply(hbefc.new_stackt,args)
        self.thisown = 1

    def __del__(self,hbefc=hbefc):
        if getattr(self,'thisown',0):
            hbefc.delete_stackt(self)
    __setmethods__ = {}
    for _s in []: __setmethods__.update(_s.__setmethods__)
    __setmethods__.update({
        "stack" : hbefc.stackt_stack_set,
        "stacksize" : hbefc.stackt_stacksize_set,
        "sp" : hbefc.stackt_sp_set,
    })
    def __setattr__(self,name,value):
        if (name == "this") or (name == "thisown"): self.__dict__[name] = value; return
        method = stackt.__setmethods__.get(name,None)
        if method: return method(self,value)
        self.__dict__[name] = value
    __getmethods__ = {}
    for _s in []: __getmethods__.update(_s.__getmethods__)
    __getmethods__.update({
        "stack" : hbefc.stackt_stack_get,
        "stacksize" : hbefc.stackt_stacksize_get,
        "sp" : hbefc.stackt_sp_get,
    })
    def __getattr__(self,name):
        method = stackt.__getmethods__.get(name,None)
        if method: return method(self)
        raise AttributeError,name
    def __repr__(self):
        return "<C stackt instance at %s>" % (self.this,)
class stacktPtr(stackt):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
        self.__class__ = stackt



class bef_interp:
    def __init__(self,*args):
        self.this = apply(hbefc.new_bef_interp,args)
        self.thisown = 1

    def __del__(self,hbefc=hbefc):
        if getattr(self,'thisown',0):
            hbefc.delete_bef_interp(self)
    def push(*args):
        val = apply(hbefc.bef_interp_push,args)
        return val
    def pop(*args):
        val = apply(hbefc.bef_interp_pop,args)
        return val
    def do(*args):
        val = apply(hbefc.bef_interp_do,args)
        return val
    __setmethods__ = {}
    for _s in []: __setmethods__.update(_s.__setmethods__)
    __setmethods__.update({
        "befungespace" : hbefc.bef_interp_befungespace_set,
        "mem" : hbefc.bef_interp_mem_set,
        "size" : hbefc.bef_interp_size_set,
        "ip" : hbefc.bef_interp_ip_set,
        "delta" : hbefc.bef_interp_delta_set,
        "stack" : hbefc.bef_interp_stack_set,
        "call" : hbefc.bef_interp_call_set,
        "CTX" : hbefc.bef_interp_CTX_set,
        "mode" : hbefc.bef_interp_mode_set,
        "prevstrchar" : hbefc.bef_interp_prevstrchar_set,
        "teleport" : hbefc.bef_interp_teleport_set,
    })
    def __setattr__(self,name,value):
        if (name == "this") or (name == "thisown"): self.__dict__[name] = value; return
        method = bef_interp.__setmethods__.get(name,None)
        if method: return method(self,value)
        self.__dict__[name] = value
    __getmethods__ = {}
    for _s in []: __getmethods__.update(_s.__getmethods__)
    __getmethods__.update({
        "befungespace" : hbefc.bef_interp_befungespace_get,
        "mem" : hbefc.bef_interp_mem_get,
        "size" : lambda x : coordPtr(hbefc.bef_interp_size_get(x)),
        "ip" : lambda x : coordPtr(hbefc.bef_interp_ip_get(x)),
        "delta" : lambda x : coordPtr(hbefc.bef_interp_delta_get(x)),
        "stack" : lambda x : stacktPtr(hbefc.bef_interp_stack_get(x)),
        "call" : lambda x : stacktPtr(hbefc.bef_interp_call_get(x)),
        "CTX" : lambda x : stacktPtr(hbefc.bef_interp_CTX_get(x)),
        "mode" : hbefc.bef_interp_mode_get,
        "prevstrchar" : hbefc.bef_interp_prevstrchar_get,
        "teleport" : hbefc.bef_interp_teleport_get,
    })
    def __getattr__(self,name):
        method = bef_interp.__getmethods__.get(name,None)
        if method: return method(self)
        raise AttributeError,name
    def __repr__(self):
        return "<C bef_interp instance at %s>" % (self.this,)
class bef_interpPtr(bef_interp):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
        self.__class__ = bef_interp





#-------------- FUNCTION WRAPPERS ------------------

strepl = hbefc.strepl

stpush = hbefc.stpush

stpeek = hbefc.stpeek

stpop = hbefc.stpop

stdig = hbefc.stdig

breplace = hbefc.breplace

push = hbefc.push

bpeek = hbefc.bpeek

pop = hbefc.pop

def bef_allocinterp(*args, **kwargs):
    val = apply(hbefc.bef_allocinterp,args,kwargs)
    if val: val = bef_interpPtr(val); val.thisown = 1
    return val

bef_free = hbefc.bef_free

bef_reset = hbefc.bef_reset

bef_do = hbefc.bef_do

bef_step = hbefc.bef_step

bef_run = hbefc.bef_run

strtoicpy = hbefc.strtoicpy

bef_loadcode = hbefc.bef_loadcode

bef_load93 = hbefc.bef_load93

def bef_loadh(*args, **kwargs):
    val = apply(hbefc.bef_loadh,args,kwargs)
    if val: val = bef_interpPtr(val); val.thisown = 1
    return val



#-------------- VARIABLE WRAPPERS ------------------

cvar = hbefc.cvar
