-- User-defined types and subtypes.
with Gnat.Io; use Gnat.Io;
procedure Subr is
   I : Integer;

   -- Creating a type equiv to integer.
   subtype Also_Int is Integer;
   Ai: Also_Int;

   -- Can limit the range of values.
   Li: Integer range 1..10;

   -- Can also create a type which has limits.
   subtype Degrees_Arc is Integer range 0..360;
   Dist: Degrees_Arc;

   -- Can "clone" a new type.
   type Temperature is new Integer;
   type Width is new Integer;
   T: Temperature;
   W: Width;
begin
   Ai := 2;
   Put("How 'bout an integer? ");
   Get(Li);
   Li := Li + Ai;
   Put("Sum is ");
   Put(Li);
   New_Line;

   Put_Line("How about temp and width?");
   Get(I);
   T := Temperature(I);
   Get(I);
   W := Width(I);
   T := T + Temperature(10);
   W := Width(2)*W;
   Put(Integer(T));
   Put(" ");
   Put(Integer(W));
   New_Line;

   -- None of these will compile:
   -- T := W;
   -- Get(T);
   -- W := 2*W;

   Put("The range of degrees is ");
   Put(Degrees_Arc'First);
   Put(" to ");
   Put(Degrees_Arc'Last);
   New_Line;
end Subr;
