
class Fridge :
    '''test'''

    def __init__(self, items={}) :
        '''init'''
        if type(items) != type({}) :
            return False;

        self.items = items;
        return;

    def __addmulti__(self, foodname, num) :
        "__addmulti def"
        if (not foodname in self.items) :
            self.items[foodname] = 0;

        self.items[foodname] = self.items[foodname] + num;
        return;

    def add_one(self, food_name) :
        if type(food_name) != type("") :
            return False;
        else :
            self.__addmulti__(food_name, 1);
        return True;

    def add_many(self, food_dict) :
        '''add_manty'''
        if type(food_dict) != type({}) :
            return False;

        for item in food_dict.keys() :
            self.__addmulti__(item, food_dict[item]);
        return ;
        
    

f = Fridge({"egga":6, "milk":2});
print(f.items);
f.add_one("apple");
print(f.items);
f.add_many({"pear":3, "grape":4});
print(f.items);

#print(dir(f));

a = {"pear":3, "grape":4};
print(a["pear"]);
try :
    print(a["apple"]);
except KeyRrror :
    print("error")

