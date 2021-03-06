/// <reference types="@types/emscripten" />

declare type EnumClass = unknown;

declare interface Deletable {
  delete(): void;
}

type Ref<T extends Deletable> = {
  [K in keyof T as Exclude<K, "delete">]: T[K];
}

interface UserImpl<T> extends T {
  __construct(): void;
  __destruct(): void;
}

type InterfaceBinding<T> = {
  extend(name: string, impl: UserImpl<T>): typeof T;
  implement(impl: UserImpl<T>): T;
};

declare class Vector<T> implements Deletable {
  constructor();

  size(): number;
  get(index: number): T;
  set(index: number, value: T): void;
  push_back(value: T): void;
  resize(newsize: number, newvalues: T): void;
  delete(): void;
}

declare class Map<K, V> implements Deletable {
  constructor();

  size(): number;
  get(key: K): V;
  set(key: K, value: V): void;
  keys(): Vector<K>;
  delete(): void;
}

declare type PinId = number;
declare type PinMode = EnumClass;
declare type Tristate = EnumClass;

declare type Pinout = Map<PinId, PinMode>;

declare type Option<T> = null | T;

declare interface IComponent {
  tick(): void;
  stable(): boolean;
  pinout(): Ref<Pinout>;
  read(pin: PinId): Tristate;
  write(pin: PinId, value: Tristate): void;
}

declare abstract class AComponent implements IComponent, Deletable {
  stable(): boolean;
  pinout(): Ref<Pinout>;
  delete(): void;
}

declare class Circuit extends AComponent {
  delete(): void;
}

declare interface IComponentFactory {
  createComponent(name: string): Option<IComponent>;
}

declare class ComboComponentFactory implements IComponentFactory, Deletable {
  constructor();

  createComponent(name: string): Option<IComponent>;
  add(factory: IComponentFactory): void;
  delete(): void;
}

declare class BuiltInComponentFactory implements IComponentFactory, Deletable {
  constructor();

  createComponent(name: string): Option<IComponent>;
  delete(): void;
}

declare class NtsCircuit extends Circuit {
  constructor();
}

export declare interface NtsModule extends EmscriptenModule {
  readonly Tristate: {
    UNDEFINED: Tristate,
    TRUE: Tristate,
    FALSE: Tristate,
  };
  readonly PinMode: {
    NONE: PinMode,
    INPUT: PinMode,
    OUTPUT: PinMode,
  };
  readonly Pinout: typeof Pinout,
  readonly IComponent: typeof IComponent,
  readonly AComponent: typeof AComponent,
  readonly Circuit: typeof Circuit,
  readonly IComponentFactory: Interface<IComponentFactory>,
  readonly ComboComponentFactory: typeof ComboComponentFactory,
  readonly BuiltInComponentFactory: typeof BuiltInComponentFactory,
  readonly NtsCircuit: typeof NtsCircuit,
}

declare const factory: EmscriptenModuleFactory<NtsModule>;

export default factory;
