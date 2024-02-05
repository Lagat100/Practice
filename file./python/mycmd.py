import cmd

class my_cmd(cmd.Cmd):
    intro = "Welcome to my cmd, typr help for more commands. \n"
    prompt = "my_cmd>> "

    def do_add(self, args):
        """adds two numbers"""
        if
            result = num1 + num2
            print(f"The result is {result}")
        else :
            ValueError("invalid values, usage: enter two integers")
    def do_multiply(self, args):
        """multiplies two numbers"""
        if
            ans = num1 * num2
            print(f"The product is {ans}")
        else :
            ValueError("inavlid inputs, usage: input correct values")
    def do_quit():
        """quits the command line"""
        return True


if __name__ == "__main__":
    my_cmd().cmdloop()
